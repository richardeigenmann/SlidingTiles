#include "debugMessageListener.h"

using namespace SlidingTiles;

DebugMessageListener::DebugMessageListener() {
    UpdatingSingleton::getInstance().add(*this);
}

DebugMessageListener::~DebugMessageListener() {
    UpdatingSingleton::getInstance().remove(*this);
}

void DebugMessageListener::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        std::cout << "DebugMessageListener received: " << msg.value() << std::endl;
    }
}