#include "debugMessageListener.h"
#include <iostream>

SlidingTiles::DebugMessageListener::DebugMessageListener() {
  UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::DebugMessageListener::~DebugMessageListener() {
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::DebugMessageListener::update(
    const float dt) { // NOLINT (misc-unused-parameters)
  auto msg = getZmqMessage();
  if (msg) {
    std::cout << "DebugMessageListener received: " << msg.value() << '\n';
  }
}