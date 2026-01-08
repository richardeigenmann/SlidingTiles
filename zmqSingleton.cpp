#include "json.hpp"
#include "zmq.hpp"
#include "zmqSingleton.h"
#include <stdexcept>         // For std::runtime_error
#include <string>

using json = nlohmann::json;

SlidingTiles::ZmqSingleton::ZmqSingleton() {
  try {
    socket.bind(std::string(PUBLISHER_SOCKET));
  } catch (const zmq::error_t &e) {
    throw std::runtime_error(
        "ZeroMQ Error when binding PublishingSingleton to socket " +
        std::string(PUBLISHER_SOCKET) + ": " + e.what());
  }
}

void SlidingTiles::ZmqSingleton::publish(const json &jsonMessage) {
  auto message = jsonMessage.dump();
  //zmq::message_t zmqMessage(message.size());
  //memcpy(zmqMessage.data(), message.data(), message.size());
  zmq::message_t zmqMessage(message.begin(), message.end());
  socket.send(zmqMessage);
}

