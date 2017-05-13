#include "game.h"
#include "gameBoard.h"
#include <cmath>
#include "puzzleSolver.h"
#include "zmqSingleton.h"
#include <fstream>
#include <random> // random_shuffle, std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <thread>
#include <sstream>
#include "json.hpp"
#include "updatingSingleton.h"


using namespace SlidingTiles;
using json = nlohmann::json;

namespace SlidingTiles {

    constexpr float Game::VICTORY_ROLL_TIME;

    Game::Game() {
        // read a JSON file and parse it
        const std::string CONFIG_FILENAME = "assets/sliding-tiles.json";
        std::cout << "Reading configuration from file: " << CONFIG_FILENAME << std::endl;
        std::ifstream configIfstream(CONFIG_FILENAME);
        if (!configIfstream) {
            throw std::runtime_error("Could not read configuration file: " + CONFIG_FILENAME);
        }
        json configJson;
        configIfstream >> configJson;
        configIfstream.close();
        levelsArray = configJson["levels"];
        winnerBlingBling.loadSounds(configJson["winnerSoundBites"]);
        attitudeSounds.loadSounds(configJson["attitudeSoundBites"]);

        levelLabel.setPosition(400, 120);
        movesLabel.setPosition(400, 150);
        parLabel.setPosition(400, 180);


        gameView.setGameBoard(&gameBoard);

        std::cout << "Game connecting to ZeroMQ socket: "
                << ZmqSingleton::RECEIVER_SOCKET << std::endl;
        contextPtr = ZmqSingleton::getInstance().getContext();
        try {
            socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
            socket->connect(ZmqSingleton::RECEIVER_SOCKET);
            socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
        } catch (const zmq::error_t & e) {
            throw std::runtime_error("ZeroMQ Error when connecting Game to socket "
                    + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
        }

        UpdatingSingleton::getInstance().add(*this);


    }

    Game::~Game() {
        UpdatingSingleton::getInstance().remove(*this);
    }

    void Game::run() {
        loadLevel();
        sf::RenderWindow* window = RenderingSingleton::getInstance().getRenderWindow();
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    doMousePressed(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 114) { //r
                        doRandomGame();
                    } else if (event.text.unicode == 112) { //p
                        gameBoard.printGame();
                    } else if (event.text.unicode == 110) { //n
                        doLevelUp();
                    } else
                        std::cout << "ASCII character typed: " << event.text.unicode << " --> " << static_cast<char> (event.text.unicode) << std::endl;
                }
            }

            sf::Time dt = deltaClock.restart();
            UpdatingSingleton::getInstance().updateAll(dt.asSeconds());
            RenderingSingleton::getInstance().renderAll();
        }
    }

    void Game::update(const float dt) {
        if (gameState == GameState::Playing) {
            std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
            if (solutionPath.size() > 0) {
                //gameBoard.setWinnerTiles(solutionPath);
                gameState = GameState::VictoryRolling;

                json jsonMessage{};
                jsonMessage["state"] = ZmqSingleton::GAME_WON;
                jsonMessage["victoryRollTime"] = VICTORY_ROLL_TIME;
                jsonMessage["moves"] = moves;
                jsonMessage["par"] = par;
                for (const auto & solutionStep : solutionPath) {
                    jsonMessage["solutionTiles"].push_back({solutionStep.x, solutionStep.y});
                }
                ZmqSingleton::getInstance().publish(jsonMessage.dump());

                victoryRollingTime = VICTORY_ROLL_TIME;
            } else {
                //gameBoard.clearWinnerTiles();
            }
        }

        if (gameState == GameState::VictoryRolling) {
            victoryRollingTime -= dt;
            if (victoryRollingTime < 0.0f) {
                doLevelUp();
                gameState = GameState::Playing;
            }
        }

        zmq::message_t reply;
        if (socket->recv(&reply, ZMQ_NOBLOCK)) {
            std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
            auto jsonMessage = json::parse(message);
            std::string state = jsonMessage["state"].get<std::string>();
            if (state == ZmqSingleton::LOAD_NEXT_LEVEL) {
                doLevelUp();
            } else if (state == ZmqSingleton::LOAD_RANDOM_LEVEL) {
                doRandomGame();
            }else if (state == ZmqSingleton::RESTART_LEVEL) {
                onRestartButtonClick();
            }
        }


    }

    void Game::onRestartButtonClick() {
        loadLevel();
        attitudeSounds.playRandomSound();
    }

    void Game::doRandomGame() {
        PuzzleSolver puzzleSolver;
        gameBoard.loadGame(puzzleSolver.generateRandomGame(3, 4).serialiseGame());
    }

    void Game::doMousePressed(const sf::Vector2i & mousePosition) {
        mousePositionPressed = mousePosition;
    }

    void Game::doMouseReleased(const sf::Vector2i & mousePosition) {
        sf::Vector2i movingTilePosition = RenderingSingleton::getInstance().findTile(mousePositionPressed);
        if (movingTilePosition.x != -1 && movingTilePosition.y != -1) {
            // out of grid
            int deltaX = mousePosition.x - mousePositionPressed.x;
            int deltaY = mousePosition.y - mousePositionPressed.y;
            if (abs(deltaX) > 2 || abs(deltaY) > 2) {
                incrementMoves();
                Tile movingTile = gameBoard.tiles[movingTilePosition.x][movingTilePosition.y];
                if (abs(deltaX) > abs(deltaY)) {
                    // horizontal movement
                    sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y);
                    if (deltaX > 0) {
                        //gameBoard.slideTile(Move{movingTilePosition, Direction::GoRight});
                        doMove(Move{movingTilePosition, Direction::GoRight});
                    } else {
                        doMove(Move{movingTilePosition, Direction::GoLeft});
                    }
                } else {
                    // vertical movement
                    sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                    if (deltaY > 0) {
                        doMove(Move{movingTilePosition, Direction::GoDown});
                    } else {
                        doMove(Move{movingTilePosition, Direction::GoUp});
                    }

                }
            }
        } else {
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::MOUSE_CLICKED;
            jsonMessage["x"] = mousePosition.x;
            jsonMessage["y"] = mousePosition.y;
            ZmqSingleton::getInstance().publish(jsonMessage.dump());
        }
    }

    void Game::doMove(const Move & move) {
        if (gameState == GameState::Playing) {
            gameBoard.slideTile(move);
        }
    }

    void Game::incrementMoves() {
        setMoves(moves + 1);
    }

    void Game::setMoves(std::size_t newMoves) {
        moves = newMoves;

        std::ostringstream movesText;
        movesText << "Moves: " << moves;
        movesLabel.setText(movesText.str());
    }

    void Game::loadLevel() {
        std::cout << "loading level " << level << std::endl;
        std::ostringstream levelText;
        levelText << "Level: " << level;
        levelLabel.setText(levelText.str());

        setMoves(0);

        json jsonLevel = levelsArray[level];
        std::string serializedGame = jsonLevel["SerializedGame"].get<std::string>();
        gameBoard.loadGame(serializedGame);
        gameState = GameState::Playing;

        par = jsonLevel["Par"].get<int>();
        std::ostringstream parText;
        parText << "Par: " << par;
        parLabel.setText(parText.str());

        json jsonMessage{};
        jsonMessage["state"] = ZmqSingleton::GAME_STARTED;
        ZmqSingleton::getInstance().publish(jsonMessage.dump());

    }

    void Game::doLevelUp() {
        ++level;
        if (level >= levelsArray.size()) {
            level = 0;
        }
        loadLevel();
    }

}
