#include "debugMessageListener.h"
#include <SFML/System/Time.hpp>
#include <iostream>

SlidingTiles::DebugMessageListener::DebugMessageListener() {
  UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::DebugMessageListener::~DebugMessageListener() {
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::DebugMessageListener::update([[maybe_unused]] const sf::Time deltaTime) {
  auto msg = getZmqMessage();
  if (msg) {
    std::cout << "DebugMessageListener received: " << msg.value() << '\n';
  }
}