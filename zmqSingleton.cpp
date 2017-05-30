#include "zmqSingleton.h"

using namespace SlidingTiles;
using json = nlohmann::json;

ZmqSingleton::ZmqSingleton() {
    try {
        socket.bind(PUBLISHER_SOCKET);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when binding PublishingSingleton to socket "
                + PUBLISHER_SOCKET + ": " + e.what());
    }
}

void ZmqSingleton::publish(const json & jsonMessage) {
    std::string message = jsonMessage.dump();
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.data(), message.size());
    socket.send(zmqMessage);
}

const std::string ZmqSingleton::PUBLISHER_SOCKET = "tcp://*:64123";
const std::string ZmqSingleton::RECEIVER_SOCKET = "tcp://localhost:64123";
const std::string ZmqSingleton::CONFIGURATION_LOADED = "Configuration Loaded";
const std::string ZmqSingleton::GAME_STARTED = "Game Started";
const std::string ZmqSingleton::GAME_WON = "Game Won";
const std::string ZmqSingleton::SET_TILE = "Set Tile";
const std::string ZmqSingleton::SLIDE_TILE = "Slide Tile";
const std::string ZmqSingleton::MOUSE_CLICKED = "Mouse Clicked";
const std::string ZmqSingleton::LOAD_NEXT_LEVEL = "Load Next Level";
const std::string ZmqSingleton::LOAD_RANDOM_LEVEL = "Load Random Level";
const std::string ZmqSingleton::RESTART_LEVEL = "Restart Level";
const std::string ZmqSingleton::DEBUG = "Debug";