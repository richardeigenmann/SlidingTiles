#include "button.h"
#include "executablePath.h"
#include "json.hpp"
#include "zmqSingleton.h"
#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>

using json = nlohmann::json;

SlidingTiles::Button::Button(const std::string &filename,
                             const std::string &command) noexcept(false)
    : command(command) {

  if (texture.loadFromFile(getAssetDir() + filename)) {
    sprite.setTexture(texture);
  } else {
    throw std::runtime_error("Failed to load texture: " + getAssetDir() +
                             filename);
  }
  RenderingSingleton::getInstance().add(*this);

  UpdatingSingleton::getInstance().add(*this);
}

/**
 * @brief Destructor
 */
SlidingTiles::Button::~Button() {
  RenderingSingleton::getInstance().remove(*this);
}

void SlidingTiles::Button::setPosition(float x, float y) {
  sprite.setPosition(x, y);
}

void SlidingTiles::Button::render() {
  if (isVisible) {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
  }
}

auto SlidingTiles::Button::mouseReleased(const sf::Vector2i &mousePosition)
    -> bool {
  return sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void SlidingTiles::Button::update(
    const float dt) { // NOLINT (misc-unused-parameters)
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(msg.value());
  }
}

void SlidingTiles::Button::handleMessage(const json &jsonMessage) {
  if (jsonMessage["state"].get<std::string>() == ZmqSingleton::MOUSE_CLICKED) {
    if (mouseReleased(sf::Vector2i{(jsonMessage["x"]), (jsonMessage["y"])})) {
      json commandMessage{};
      commandMessage["state"] = command;
      ZmqSingleton::getInstance().publish(commandMessage);
    }
  }
}
