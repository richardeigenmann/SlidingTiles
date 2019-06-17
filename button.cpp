#include "button.h"
#include "json.hpp"
#include "zmqSingleton.h"


using json = nlohmann::json;

SlidingTiles::Button::Button(const std::string & filename, const std::string & command) : command(command) {
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
SlidingTiles::Button::~Button() {
    RenderingSingleton::getInstance().remove(*this);
}

void SlidingTiles::Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void SlidingTiles::Button::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}

bool SlidingTiles::Button::mouseReleased(const sf::Vector2i & mousePosition) {
    return sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void SlidingTiles::Button::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void SlidingTiles::Button::handleMessage(const json & jsonMessage) {
    auto state = jsonMessage["state"].get<std::string>();
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
