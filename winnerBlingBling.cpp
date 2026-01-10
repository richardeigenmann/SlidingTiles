#include "winnerBlingBling.h"
#include "executablePath.h"
#include "gameState.h"
#include "zmqSingleton.h"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

SlidingTiles::WinnerBlingBling::WinnerBlingBling() noexcept(false) {
  const std::string filename{getAssetDir() + "trophy.png"};
  if (texture.loadFromFile(filename)) {
    sprite.setTexture(texture);
  } else {
    throw std::runtime_error("Failed to load texture: " + filename);
  }

  const auto position = sf::Vector2f {400, 5};
  setPosition( position );
  const float SCALE{0.2F};
  sprite.setScale(SCALE, SCALE);
  RenderingSingleton::getInstance().add(*this);
  UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::WinnerBlingBling::~WinnerBlingBling() {
  RenderingSingleton::getInstance().remove(*this);
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::WinnerBlingBling::loadSounds(const json &jsonArray) {
  winnerSounds.loadSounds(jsonArray);
}

void SlidingTiles::WinnerBlingBling::setPosition(const sf::Vector2f& position) {
  sprite.setPosition( position );
}

void SlidingTiles::WinnerBlingBling::startBlingBling(std::size_t moves,
                                                     std::size_t par) {
  if (moves == par) {
    winnerSounds.playRandomSound();
  }
  gameState = GameState::VictoryRolling;
}

void SlidingTiles::WinnerBlingBling::endBlingBling() {
  gameState = GameState::Playing;
}

void SlidingTiles::WinnerBlingBling::update([[maybe_unused]] const sf::Time deltaTime) {
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(*msg);
  }
}

void SlidingTiles::WinnerBlingBling::handleMessage(const json &jsonMessage) {
  auto state = jsonMessage["state"].get<std::string_view>();
  if (state == ZmqSingleton::CONFIGURATION_LOADED) {
    loadSounds(jsonMessage["winnerSoundBites"]);
  } else if (state == ZmqSingleton::GAME_WON) {
    startBlingBling(jsonMessage["moves"], jsonMessage["par"]);
  } else if (state == ZmqSingleton::GAME_STARTED) {
    endBlingBling();
  }
}

void SlidingTiles::WinnerBlingBling::render() {
  if (gameState == GameState::VictoryRolling) {
    RenderingSingleton::getInstance().getRenderWindow()->draw(
        sprite);
  }
}
