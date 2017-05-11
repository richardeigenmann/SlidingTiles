#include "button.h"
#include <iostream>


using namespace SlidingTiles;

Button::Button(const std::string & filename) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    RenderingSingleton::getInstance().add(*this);
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
