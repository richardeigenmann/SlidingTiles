#include "attitudeSoundPlayer.h"
#include "json.hpp"
#include "zmq.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;


SlidingTiles::AttitudeSoundPlayer::AttitudeSoundPlayer() {
    UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::AttitudeSoundPlayer::~AttitudeSoundPlayer() {
    UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::AttitudeSoundPlayer::update(const float dt) { // NOLINT (misc-unused-parameters)
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}


void SlidingTiles::AttitudeSoundPlayer::handleMessage(const nlohmann::json & jsonMessage) {
        auto state = jsonMessage["state"].get<std::string>();
        if (state == SlidingTiles::ZmqSingleton::CONFIGURATION_LOADED) {
            loadSounds(jsonMessage["attitudeSoundBites"]);
        } else if (state == SlidingTiles::ZmqSingleton::RESTART_LEVEL) {
            playRandomSound();
        }
}