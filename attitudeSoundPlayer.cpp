#include "attitudeSoundPlayer.h"

using namespace SlidingTiles;
using json = nlohmann::json;

AttitudeSoundPlayer::AttitudeSoundPlayer() {
    UpdatingSingleton::getInstance().add(*this);
    
    std::cout << "AttitudeSoundPlayer connecting to ZeroMQ socket: "
            << ZmqSingleton::RECEIVER_SOCKET << std::endl;
    contextPtr = ZmqSingleton::getInstance().getContext();
    try {
        socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
        socket->connect(ZmqSingleton::RECEIVER_SOCKET);
        socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when connecting AttitudeSoundPlayer to socket "
                + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
    }
}

AttitudeSoundPlayer::~AttitudeSoundPlayer() {
    socket->close();
    UpdatingSingleton::getInstance().remove(*this);
}

void AttitudeSoundPlayer::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
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