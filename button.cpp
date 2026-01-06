#include "button.h"
#include "executablePath.h"
#include "json.hpp"
#include "strongTypes.h"
#include "zmqSingleton.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

using json = nlohmann::json;

SlidingTiles::Button::Button(const AssetPath &filename,
                             std::string command) noexcept(false)
    : command(std::move(command)) {

  texture = std::make_unique<sf::Texture>();
  if (texture->loadFromFile(getAssetDir() + filename.value)) {
    sprite.setTexture(*texture);
  } else {
    throw std::runtime_error("Failed to load texture: " + getAssetDir() + filename.value);
  }
  RenderingSingleton::getInstance().add(*this);
  UpdatingSingleton::getInstance().add(*this);
}

/**
 * @brief Destructor
 */
SlidingTiles::Button::~Button() {
  RenderingSingleton::getInstance().remove(*this);
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::Button::setPosition(float x, float y) {
  sprite.setPosition(x, y);
}

void SlidingTiles::Button::render() {
  if (isVisible) {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
  }
}

auto SlidingTiles::Button::mouseReleased(const sf::Vector2i &mousePosition) -> bool {
  return sprite.getGlobalBounds().contains(sf::Vector2f(mousePosition));
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
