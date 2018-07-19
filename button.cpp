#include "button.h"
#include "zmqSingleton.h"
#include "json.hpp"

using namespace SlidingTiles;
using json = nlohmann::json;

Button::Button(const std::string & filename, const std::string & command) : command(command) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    RenderingSingleton::getInstance().add(*this);

    UpdatingSingleton::getInstance().add(*this);
}

/**
 * @brief Destructor
 */
Button::~Button() {
    RenderingSingleton::getInstance().remove(*this);
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Button::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}

bool Button::mouseReleased(const sf::Vector2i & mousePosition) {
    return sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void Button::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void Button::handleMessage(const json & jsonMessage) {
    std::string state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::MOUSE_CLICKED) {
        int x = jsonMessage["x"];
        int y = jsonMessage["y"];
        if (mouseReleased(sf::Vector2i{x, y})) {
            json commandMessage{};
            commandMessage["state"] = command;
            ZmqSingleton::getInstance().publish(commandMessage);
        }
    }
}
