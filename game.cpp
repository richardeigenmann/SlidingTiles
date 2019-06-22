#include "game.h"
#include "gameBoard.h"
#include "json.hpp"
#include "puzzleSolver.h"
#include "updatingSingleton.h"
#include "zmqSingleton.h"
#include <chrono> // std::chrono::system_clock
#include <cmath>
#include <fstream>
#include <random> // random_shuffle, std::default_random_engine
#include <sstream>
#include <thread>

using json = nlohmann::json;

namespace SlidingTiles {

    Game::Game() { // NOLINT (fuchsia-default-arguments)
        // read a JSON file and parse it
        const std::string CONFIG_FILENAME = "assets/sliding-tiles.json"; // NOLINT (fuchsia-default-arguments)
        std::cout << "Reading configuration from file: " << CONFIG_FILENAME << std::endl;
        std::ifstream configIfstream(CONFIG_FILENAME); // NOLINT (fuchsia-default-arguments)
        if (!configIfstream) {
            throw std::runtime_error("Could not read configuration file: " + CONFIG_FILENAME);
        }
        json configJson; // NOLINT (fuchsia-default-arguments)
        configIfstream >> configJson;
        configIfstream.close();

        // send the configuration to all listeners
        configJson["state"] = ZmqSingleton::CONFIGURATION_LOADED;
        ZmqSingleton::getInstance().publish(configJson);

        gameView.setGameBoard(&gameBoard);
        UpdatingSingleton::getInstance().add(*this);
    }

    Game::~Game() {
        UpdatingSingleton::getInstance().remove(*this);
    }

    void Game::run() {
        sf::RenderWindow* window = RenderingSingleton::getInstance().getRenderWindow();
        while (window->isOpen()) {
            sf::Event event {};
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    doMousePressed(sf::Vector2i{event.mouseButton.x, event.mouseButton.y}); // NOLINT(cppcoreguidelines-pro-type-union-access)
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i{event.mouseButton.x, event.mouseButton.y}); // NOLINT(cppcoreguidelines-pro-type-union-access)
                } else if (event.type == sf::Event::TextEntered) {
                    const unsigned int LOWERCASE_R { 114 };
                    const unsigned int LOWERCASE_P { 112 };
                    const unsigned int LOWERCASE_N { 110 };
                    const unsigned int LOWERCASE_D { 100 };
                    if (event.text.unicode == LOWERCASE_R) { // NOLINT(cppcoreguidelines-pro-type-union-access)
                        doRandomGame();
                    } else if (event.text.unicode == LOWERCASE_P) { // NOLINT(cppcoreguidelines-pro-type-union-access)
                        gameBoard.printGame();
                    } else if (event.text.unicode == LOWERCASE_N) {  // NOLINT(cppcoreguidelines-pro-type-union-access)
                        doLevelUp();
                    } else { 
                        if (event.text.unicode == LOWERCASE_D) { //d // NOLINT(cppcoreguidelines-pro-type-union-access)
                            json jsonMessage{}; // NOLINT (fuchsia-default-arguments)
                            jsonMessage["state"] = ZmqSingleton::DEBUG;
                            ZmqSingleton::getInstance().publish(jsonMessage);
                        } else {
                            std::cout << "ASCII character typed: " << event.text.unicode << " --> " << static_cast<char> (event.text.unicode) << std::endl; // NOLINT (cppcoreguidelines-pro-type-union-access)
                        }
                    }
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
            if ( ! solutionPath.empty() ) {
                gameState = GameState::VictoryRolling;

                json jsonMessage{}; // NOLINT (fuchsia-default-arguments)
                jsonMessage["state"] = ZmqSingleton::GAME_WON;
                jsonMessage["victoryRollTime"] = Game::VICTORY_ROLL_TIME;
                jsonMessage["moves"] = moves;
                jsonMessage["par"] = levelsArray[level]["Par"].get<int>();
                for (const auto & solutionStep : solutionPath) {
                    jsonMessage["solutionTiles"].push_back({solutionStep.x, solutionStep.y});
                }
                ZmqSingleton::getInstance().publish(jsonMessage);

                victoryRollingTime = Game::VICTORY_ROLL_TIME;
            }
        }

        if (gameState == GameState::VictoryRolling) {
            victoryRollingTime -= dt;
            if (victoryRollingTime < 0.0F) {
                doLevelUp();
                gameState = GameState::Playing;
            }
        }

        auto msg = getZmqMessage();
        if (msg) {
            handleMessage(msg.value());
        }
    }

    void Game::handleMessage(const json & jsonMessage) {
        auto state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::CONFIGURATION_LOADED) {
            levelsArray = jsonMessage["levels"];
            loadLevel();
        } else if (state == ZmqSingleton::LOAD_NEXT_LEVEL) {
            doLevelUp();
        } else if (state == ZmqSingleton::LOAD_RANDOM_LEVEL) {
            doRandomGame();
        } else if (state == ZmqSingleton::RESTART_LEVEL) {
            onRestartButtonClick();
        }
    }
    void Game::onRestartButtonClick() {
        loadLevel();
    }

    void Game::doRandomGame() {
        PuzzleSolver puzzleSolver;
        const unsigned int EMPTY_TILES {8};
        const unsigned int DEPTH {2};
        gameBoard.loadGame(puzzleSolver.generateRandomGame(EMPTY_TILES, DEPTH).serialiseGame());
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
                if (abs(deltaX) > abs(deltaY)) {
                    // horizontal movement
                    sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y); // NOLINT (bugprone-narrowing-conversions)
                    if (deltaX > 0) {
                        doMove(Move{movingTilePosition, Direction::GoRight});
                    } else {
                        doMove(Move{movingTilePosition, Direction::GoLeft});
                    }
                } else {
                    // vertical movement
                    sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY)); // NOLINT (bugprone-narrowing-conversions)
                    if (deltaY > 0) {
                        doMove(Move{movingTilePosition, Direction::GoDown});
                    } else {
                        doMove(Move{movingTilePosition, Direction::GoUp});
                    }

                }
            }
        } else {
            json jsonMessage{}; // NOLINT (fuchsia-default-arguments)
            jsonMessage["state"] = ZmqSingleton::MOUSE_CLICKED;
            jsonMessage["x"] = mousePosition.x;
            jsonMessage["y"] = mousePosition.y;
            ZmqSingleton::getInstance().publish(jsonMessage);
        }
    }

    void Game::doMove(const Move & move) {
        incrementMoves();
        if (gameState == GameState::Playing) {
            gameBoard.slideTile(move);
        }
    }

    void Game::incrementMoves() {
        setMoves(moves + 1);
    }

    void Game::setMoves(std::size_t newMoves) {
        moves = newMoves;
    }

    void Game::loadLevel() {
        setMoves(0);

        json jsonLevel = levelsArray[level];
        auto serializedGame = jsonLevel["SerializedGame"].get<std::string>();
        gameBoard.loadGame(serializedGame);
        gameState = GameState::Playing;

        json jsonMessage{}; // NOLINT (fuchsia-default-arguments)
        jsonMessage["state"] = ZmqSingleton::GAME_STARTED;
        jsonMessage["level"] = level;
        jsonMessage["par"] = jsonLevel["Par"].get<int>();
        ZmqSingleton::getInstance().publish(jsonMessage);
    }

    void Game::doLevelUp() {
        ++level;
        if (level >= levelsArray.size()) {
            level = 0;
        }
        loadLevel();
    }

} // namespace SlidingTiles
