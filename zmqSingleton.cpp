#include "zmqSingleton.h"

using json = nlohmann::json;

SlidingTiles::ZmqSingleton::ZmqSingleton() {
    try {
        socket.bind(PUBLISHER_SOCKET);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when binding PublishingSingleton to socket "
                + PUBLISHER_SOCKET + ": " + e.what());
    }
}

void SlidingTiles::ZmqSingleton::publish(const json & jsonMessage) {
    auto message = jsonMessage.dump(); // NOLINT (fuchsia-default-arguments)
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.data(), message.size());
    socket.send(zmqMessage); // NOLINT (fuchsia-default-arguments)
}

//const std::string ZmqSingleton::PUBLISHER_SOCKET = "tcp://*:64123";
const std::string SlidingTiles::ZmqSingleton::PUBLISHER_SOCKET = "inproc://#1"; // NOLINT (fuchsia-default-arguments)
//const std::string ZmqSingleton::RECEIVER_SOCKET = "tcp://localhost:64123";
const std::string SlidingTiles::ZmqSingleton::RECEIVER_SOCKET = "inproc://#1"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::CONFIGURATION_LOADED = "Configuration Loaded"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::GAME_STARTED = "Game Started"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::GAME_WON = "Game Won"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::SET_TILE = "Set Tile"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::SLIDE_TILE = "Slide Tile"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::MOUSE_CLICKED = "Mouse Clicked"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::LOAD_NEXT_LEVEL = "Load Next Level"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::LOAD_RANDOM_LEVEL = "Load Random Level"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::RESTART_LEVEL = "Restart Level"; // NOLINT (fuchsia-default-arguments)
const std::string SlidingTiles::ZmqSingleton::DEBUG = "Debug"; // NOLINT (fuchsia-default-arguments)