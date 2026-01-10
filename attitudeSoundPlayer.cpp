#include "attitudeSoundPlayer.h"
#include "json.hpp"
#include "zmqSingleton.h"
#include <string_view>

using json = nlohmann::json;

SlidingTiles::AttitudeSoundPlayer::AttitudeSoundPlayer() {
  UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::AttitudeSoundPlayer::~AttitudeSoundPlayer() {
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::AttitudeSoundPlayer::update([[maybe_unused]] const sf::Time deltaTime) {
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(*msg);
  }
}

void SlidingTiles::AttitudeSoundPlayer::handleMessage(const nlohmann::json &jsonMessage) {
  auto state = jsonMessage["state"].get<std::string_view>();
  if (state == SlidingTiles::ZmqSingleton::CONFIGURATION_LOADED) {
    loadSounds(jsonMessage["attitudeSoundBites"]);
  } else if (state == SlidingTiles::ZmqSingleton::RESTART_LEVEL) {
    playRandomSound();
  }
}
