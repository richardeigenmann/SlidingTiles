#include "attitudeSoundPlayer.h"
#include "json.hpp"
#include "zmq.hpp"
#include <iostream>
#include <string>

using namespace SlidingTiles;
using json = nlohmann::json;


AttitudeSoundPlayer::AttitudeSoundPlayer() {
    UpdatingSingleton::getInstance().add(*this);
}

AttitudeSoundPlayer::~AttitudeSoundPlayer() {
    UpdatingSingleton::getInstance().remove(*this);
}

void AttitudeSoundPlayer::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}


void AttitudeSoundPlayer::handleMessage(const nlohmann::json & jsonMessage) {
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::CONFIGURATION_LOADED) {
            loadSounds(jsonMessage["attitudeSoundBites"]);
        } else if (state == ZmqSingleton::RESTART_LEVEL) {
            playRandomSound();
        }
}