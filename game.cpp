#include "game.h"
#include "gameBoard.h"
#include <cmath>
#include "puzzleSolver.h"
#include "publishingSingleton.h"
#include <fstream>
#include <random> // random_shuffle, std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <sstream>
#include "json.hpp"


using namespace SlidingTiles;
using json = nlohmann::json;

namespace SlidingTiles {

    constexpr float Game::VICTORY_ROLL_TIME;

    Game::Game() {
        // read a JSON file
        const std::string CONFIG_FILENAME = "assets/sliding-tiles.json";
        std::ifstream in(CONFIG_FILENAME);
        if (!in) {
            std::cerr << "Could not read configuration file: "
                    << CONFIG_FILENAME << std::endl;
        }
        json j;
        in >> j;
        levelsArray = j["levels"];

        for (int y = 0; y < gameBoard.boardSize; ++y) {
            for (int x = 0; x < gameBoard.boardSize; ++x) {
                //TileView* tileView = new TileView(sf::Vector2i{x,y});
                std::cout << "Creating a TileView for x: " << x << " y: " << y << "\n";
                std::unique_ptr<TileView> tileView(new TileView(sf::Vector2i{x, y}));
                gameBoard.tiles[x][y].add(*tileView);
                tileViews.push_back(std::move(tileView));
            }
        }

        loadLevel();

        gameView.setGameBoard(&gameBoard);

        json winnerSoundBitesArray = j["winnerSoundBites"];
        winnerBlingBling.loadSounds(winnerSoundBitesArray);

        json attitudeSoundBitesArray = j["attitudeSoundBites"];
        attitudeSounds.loadSounds(attitudeSoundBitesArray);

        levelLabel.setPosition(400, 120);
        movesLabel.setPosition(400, 150);
        parLabel.setPosition(400, 180);
        randomSfmlButton.setPosition(400, 230);
        nextSfmlButton.setPosition(400, 270);
        restartSfmlButton.setPosition(400, 310);
    }

    void Game::update(const float & dt) {
        // send update event to all the tiles
        for (int x = 0; x < GameBoard::boardSize; ++x)
            for (int y = 0; y < GameBoard::boardSize; ++y) {
                gameBoard.tiles[x][y].update(dt);
            }

        if (gameState == GameState::Playing) {
            std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
            if (solutionPath.size() > 0) {
                gameBoard.setWinnerTiles(solutionPath);
                gameState = GameState::VictoryRolling;

                json jsonMessage{};
                jsonMessage["state"] = PublishingSingleton::GAME_WON;
                jsonMessage["victoryRollTime"] = VICTORY_ROLL_TIME;
                jsonMessage["moves"] = moves;
                jsonMessage["par"] = par;

                PublishingSingleton::getInstance().publish(jsonMessage.dump());

                victoryRollingTime = VICTORY_ROLL_TIME;
            } else {
                gameBoard.clearWinnerTiles();
            }
        }


        if (gameState == GameState::VictoryRolling) {
            victoryRollingTime -= dt;
            if (victoryRollingTime < 0.0f) {
                doLevelUp();
                gameState = GameState::Playing;
            }
        }
        winnerBlingBling.update(dt);
    }

    void Game::onRandomButtonClick() {
        doRandomGame();
    }

    void Game::onNextButtonClick() {
        doLevelUp();
    }

    void Game::onRestartButtonClick() {
        loadLevel();
        attitudeSounds.playRandomSound();
    }

    void Game::run() {
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
            update(dt.asSeconds());
            RenderingSingleton::getInstance().renderAll();
        }
    }

    void Game::doRandomGame() {
        PuzzleSolver puzzleSolver;
        gameBoard.loadGame(puzzleSolver.generateRandomGame(3, 4).serialiseGame());
    }

    void Game::doMousePressed(const sf::Vector2i & mousePosition) {
        mousePositionPressed = mousePosition;
    }

    void Game::doMouseReleased(const sf::Vector2i & mousePosition) {
        if (nextSfmlButton.mouseReleased(mousePosition)) {
            onNextButtonClick();
            return;
        } else if (randomSfmlButton.mouseReleased(mousePosition)) {
            onRandomButtonClick();
            return;
        } else if (restartSfmlButton.mouseReleased(mousePosition)) {
            onRestartButtonClick();
            return;
        }

        sf::Vector2i movingTilePosition = RenderingSingleton::getInstance().findTile(mousePositionPressed);
        if (movingTilePosition.x == -1 || movingTilePosition.y == -1)
            return; // out of grid
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
        jsonMessage["state"] = PublishingSingleton::GAME_STARTED;
        PublishingSingleton::getInstance().publish(jsonMessage.dump());

    }

    void Game::doLevelUp() {
        ++level;
        if (level >= levelsArray.size()) {
            level = 0;
        }
        loadLevel();
    }

}
