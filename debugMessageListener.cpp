#include "debugMessageListener.h"

using namespace SlidingTiles;

DebugMessageListener::DebugMessageListener() {
    UpdatingSingleton::getInstance().add(*this);
}

DebugMessageListener::~DebugMessageListener() {
    UpdatingSingleton::getInstance().remove(*this);
}

void DebugMessageListener::update(const float dt) {
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        std::cout << "DebugMessageListener received: " << message << std::endl;
    }

}