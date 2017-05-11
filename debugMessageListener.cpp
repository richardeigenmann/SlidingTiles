#include "debugMessageListener.h"

using namespace SlidingTiles;

DebugMessageListener::DebugMessageListener() {
    UpdatingSingleton::getInstance().add(*this);

    std::cout << "DebugMessageListener connecting to ZeroMQ socket: " << PublishingSingleton::RECEIVER_SOCKET << std::endl;
    context = PublishingSingleton::getInstance().getContext();
    socket = new zmq::socket_t{*context, ZMQ_SUB};
    socket->connect(PublishingSingleton::RECEIVER_SOCKET);
    socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
    UpdatingSingleton::getInstance().add(*this);
}

DebugMessageListener::~DebugMessageListener() {
    socket->close();
    delete socket;
    UpdatingSingleton::getInstance().remove(*this);
}

void DebugMessageListener::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        std::cout << "DebugMessageListener received: " << message << std::endl;
    }
}