#include "label.h"

using namespace SlidingTiles;

Label::Label() {
    if (!font.loadFromFile("assets/Raleway-Regular.ttf"))
        std::cout << "Can't load font ./assets/Raleway-Regular.ttf" << std::endl;

    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::Black);
    RenderingSingleton::getInstance().add(*this);
}

void Label::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void Label::setText(std::string newText) {
    text.setString(newText);
}

void Label::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(text);
}