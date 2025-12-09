#include "zmqSingleton.h"

using json = nlohmann::json;

SlidingTiles::ZmqSingleton::ZmqSingleton() {
  try {
    socket.bind(PUBLISHER_SOCKET);
  } catch (const zmq::error_t &e) {
    throw std::runtime_error(
        "ZeroMQ Error when binding PublishingSingleton to socket " +
        PUBLISHER_SOCKET + ": " + e.what());
  }
}

void SlidingTiles::ZmqSingleton::publish(const json &jsonMessage) {
  auto message = jsonMessage.dump();
  zmq::message_t zmqMessage(message.size());
  memcpy(zmqMessage.data(), message.data(), message.size());
  socket.send(zmqMessage);
}

// const std::string ZmqSingleton::PUBLISHER_SOCKET = "tcp://*:64123";
const std::string SlidingTiles::ZmqSingleton::PUBLISHER_SOCKET = "inproc://#1";
// const std::string ZmqSingleton::RECEIVER_SOCKET = "tcp://localhost:64123";
const std::string SlidingTiles::ZmqSingleton::RECEIVER_SOCKET = "inproc://#1";
const std::string SlidingTiles::ZmqSingleton::CONFIGURATION_LOADED =
    "Configuration Loaded";
const std::string SlidingTiles::ZmqSingleton::GAME_STARTED = "Game Started";
const std::string SlidingTiles::ZmqSingleton::OVER_PAR = "Over Par";
const std::string SlidingTiles::ZmqSingleton::GAME_WON = "Game Won";
const std::string SlidingTiles::ZmqSingleton::SET_TILE = "Set Tile";
const std::string SlidingTiles::ZmqSingleton::SLIDE_TILE = "Slide Tile";
const std::string SlidingTiles::ZmqSingleton::MOUSE_CLICKED = "Mouse Clicked";
const std::string SlidingTiles::ZmqSingleton::LOAD_NEXT_LEVEL =
    "Load Next Level";
const std::string SlidingTiles::ZmqSingleton::LOAD_RANDOM_LEVEL =
    "Load Random Level";
const std::string SlidingTiles::ZmqSingleton::UNDO_MOVE = "Undo Move";
const std::string SlidingTiles::ZmqSingleton::RESTART_LEVEL = "Restart Level";
const std::string SlidingTiles::ZmqSingleton::BROADCAST_MOVES_COUNT =
    "Broadcast Moves Count";
const std::string SlidingTiles::ZmqSingleton::DEBUG = "Debug";