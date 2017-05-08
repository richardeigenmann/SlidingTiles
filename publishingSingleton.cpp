#include "publishingSingleton.h"
#include <iostream>

using namespace SlidingTiles;

PublishingSingleton::PublishingSingleton() {
    try {
        socket.bind(PUBLISHER_SOCKET);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when binding PublishingSingleton to socket " + PUBLISHER_SOCKET + ": " + e.what());
    }
}

void PublishingSingleton::publish(const std::string & message) {
    // prepare the message
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.data(), message.size());

    //  Send message to all subscribers
    socket.send(zmqMessage);
    std::cout << "Sent message: " << message << std::endl;
}

const std::string PublishingSingleton::PUBLISHER_SOCKET = "tcp://*:64123";
const std::string PublishingSingleton::RECEIVER_SOCKET = "tcp://localhost:64123";
const std::string PublishingSingleton::INITIALISING = "Initialising";
const std::string PublishingSingleton::GAME_STARTED = "Game Started";
const std::string PublishingSingleton::GAME_WON = "Game Won";
const std::string PublishingSingleton::SET_TILE = "Set Tile";
const std::string PublishingSingleton::SLIDE_TILE = "Slide Tile";
