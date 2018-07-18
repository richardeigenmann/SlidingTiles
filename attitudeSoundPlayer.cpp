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
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::CONFIGURATION_LOADED) {
            loadSounds(jsonMessage["attitudeSoundBites"]);
        } else if (state == ZmqSingleton::RESTART_LEVEL) {
            playRandomSound();
        }
    }
}