#include "debugMessageListener.h"

using namespace SlidingTiles;

DebugMessageListener::DebugMessageListener() {
    UpdatingSingleton::getInstance().add(*this);

    std::cout << "DebugMessageListener connecting to ZeroMQ socket: "
            << ZmqSingleton::RECEIVER_SOCKET << std::endl;
    contextPtr = ZmqSingleton::getInstance().getContext();
    try {
        socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
        socket->connect(ZmqSingleton::RECEIVER_SOCKET);
        socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when connecting Button to socket "
                + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
    }
}

DebugMessageListener::~DebugMessageListener() {
    socket->close();
    UpdatingSingleton::getInstance().remove(*this);
}

void DebugMessageListener::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        std::cout << "DebugMessageListener received: " << message << std::endl;
    }
}