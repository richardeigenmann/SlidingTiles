#include "button.h"
#include <iostream>


using namespace SlidingTiles;

Button::Button(const std::string & filename) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    RenderingSingleton::getInstance().add(*this);
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
