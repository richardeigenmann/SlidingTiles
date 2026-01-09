#include "direction.h"
#include "executablePath.h"
#include "game.h"
#include "gameBoard.h"
#include "gameState.h"
#include "json.hpp"
#include "puzzleSolver.h"
#include "renderingSingleton.h"
#include "updatingSingleton.h"
#include "zmqSingleton.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace SlidingTiles {

Game::Game() noexcept(false) {
  loadAndPublishConfigFile();

  gameView.setGameBoard(&gameBoard);
  UpdatingSingleton::getInstance().add(*this);
}

Game::~Game() { UpdatingSingleton::getInstance().remove(*this); }

auto Game::loadConfigFile(const std::string &filename) -> nlohmann::json {
  std::cout << "Reading configuration from file: " << filename << '\n';
  std::ifstream configIfstream(filename);
  if (!configIfstream) {
    throw std::runtime_error("Could not read configuration file: " + filename);
  }
  json configJson;
  configIfstream >> configJson;
  configIfstream.close();
  std::cout << "Read & parsed configuration from file: " << filename
            << '\n';
  return configJson;
}

void Game::loadAndPublishConfigFile() {
  const std::string CONFIG_FILENAME = getAssetDir() + "sliding-tiles.json";
  json configJson = loadConfigFile(CONFIG_FILENAME);

  configJson["state"] = ZmqSingleton::CONFIGURATION_LOADED;
  ZmqSingleton::getInstance().publish(configJson);
}

void Game::run() {
  sf::RenderWindow *window =
      RenderingSingleton::getInstance().getRenderWindow();
  while (window->isOpen()) {
    sf::Event event{};
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      } else if (event.type == sf::Event::MouseButtonPressed) {
        doMousePressed(sf::Vector2i{
            event.mouseButton.x,
            event.mouseButton.y
        });
      } else if (event.type == sf::Event::MouseButtonReleased) {
        doMouseReleased(sf::Vector2i{
            event.mouseButton.x,
            event.mouseButton
                .y}); // NOLINT(cppcoreguidelines-pro-type-union-access)
      } else if (event.type == sf::Event::TextEntered) {
        const unsigned int LOWERCASE_R{114};
        const unsigned int LOWERCASE_P{112};
        const unsigned int LOWERCASE_N{110};
        const unsigned int LOWERCASE_D{100};
        // sf::Event is a union and not a C++17 std::variant which would be
        // better NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
        if (event.text.unicode == LOWERCASE_R) {
          doRandomGame();
        } else if (
            event.text.unicode ==
            LOWERCASE_P) { // NOLINT(cppcoreguidelines-pro-type-union-access)
          gameBoard.printGame();
        } else if (
            event.text.unicode ==
            LOWERCASE_N) { // NOLINT(cppcoreguidelines-pro-type-union-access)
          doLevelUp();
        } else {
          if (event.text.unicode ==
              LOWERCASE_D) { // NOLINT(cppcoreguidelines-pro-type-union-access)
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::DEBUG;
            ZmqSingleton::getInstance().publish(jsonMessage);
          } else {
            std::cout << "ASCII character typed: " << event.text.unicode
                      << " --> " << static_cast<char>(event.text.unicode)
                      << std::endl; // NOLINT
                                    // (cppcoreguidelines-pro-type-union-access)
          }
        }
      }
    }
    const sf::Time deltaTime = deltaClock.restart();
    UpdatingSingleton::getInstance().updateAll(deltaTime.asSeconds());
    RenderingSingleton::getInstance().renderAll();
  }
}

void Game::update(const float deltaTime) {
  if (gameState == GameState::Playing || gameState == GameState::OverPar) {
    const std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
    if (!solutionPath.empty()) {
      gameState = GameState::VictoryRolling;

      json jsonMessage{};
      jsonMessage["state"] = ZmqSingleton::GAME_WON;
      jsonMessage["victoryRollTime"] = Game::VICTORY_ROLL_TIME;
      jsonMessage["moves"] = gameBoard.moves.size();
      jsonMessage["par"] = levelsArray[level]["Par"].get<int>();
      for (const auto &solutionStep : solutionPath) {
        jsonMessage["solutionTiles"].push_back(
            {solutionStep.x, solutionStep.y});
      }
      ZmqSingleton::getInstance().publish(jsonMessage);

      victoryRollingTime = Game::VICTORY_ROLL_TIME;
    } else {
      if (gameState == GameState::Playing &&
          gameBoard.moves.size() == levelsArray[level]["Par"].get<int>()) {
        gameState = GameState::OverPar;
        json jsonMessage{};
        jsonMessage["state"] = ZmqSingleton::OVER_PAR;
        ZmqSingleton::getInstance().publish(jsonMessage);
      }
    }
  }

  if (gameState == GameState::VictoryRolling) {
    victoryRollingTime -= deltaTime;
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

void Game::handleMessage(const json &jsonMessage) {
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
  } else if (state == ZmqSingleton::UNDO_MOVE) {
    gameBoard.undoLatestMove();
  }
}

void Game::onRestartButtonClick() { loadLevel(); }

void Game::doRandomGame() {
  const PuzzleSolver puzzleSolver;
  const unsigned int EMPTY_TILES{8};
  const unsigned int DEPTH{2};
  std::cout << "Generating a random game\n";
  auto randomGameBoard = SlidingTiles::PuzzleSolver::generateRandomGame(GameSettings{EMPTY_TILES, DEPTH});
  auto serialisedBoard = randomGameBoard.serialiseGameToWstring();
  gameBoard.loadGame(serialisedBoard);
}

void Game::doMousePressed(const sf::Vector2i &mousePosition) {
  mousePositionPressed = mousePosition;
}

void Game::doMouseReleased(const sf::Vector2i &mousePosition) {
  const sf::Vector2i movingTilePosition =
      RenderingSingleton::getInstance().findTile(mousePositionPressed);
  if (movingTilePosition.x != -1 && movingTilePosition.y != -1) {
    // out of grid
    const int deltaX = mousePosition.x - mousePositionPressed.x;
    const int deltaY = mousePosition.y - mousePositionPressed.y;
    if (abs(deltaX) > 2 || abs(deltaY) > 2) {
      if (abs(deltaX) > abs(deltaY)) {
        // horizontal movement
        if (deltaX > 0) {
          doMove(Move{movingTilePosition, Direction::GoRight});
        } else {
          doMove(Move{movingTilePosition, Direction::GoLeft});
        }
      } else {
        // vertical movement
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
    ZmqSingleton::getInstance().publish(jsonMessage);
 }
}

void Game::doMove(const Move &move) {
  if (gameState == GameState::Playing || gameState == GameState::OverPar) {
    gameBoard.moveTile(move);
  }
}

void Game::loadLevel() {
  gameBoard.moves.clear();

  const json& jsonLevel = levelsArray[level];
  auto serializedGame = jsonLevel["SerializedGame"].get<std::string>();
  const std::wstring wide = sf::String::fromUtf8(serializedGame.begin(), serializedGame.end()).toWideString();
  std::wcout << L"wide string: " << wide << '\n';
  gameBoard.loadGame(wide);
  gameState = GameState::Playing;

  json jsonMessage{};
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
