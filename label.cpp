#include "label.h"

using namespace SlidingTiles;

Label::Label() {
    if (!font.loadFromFile("assets/Raleway-Regular.ttf"))
        std::cout << "Can't load font ./assets/Raleway-Regular.ttf" << std::endl;

    text.setFont(font);
    text.setCharacterSize(16);

    // Travis uses an old Ubuntu that only has SFML 2.1 which doesn't have setFillColor and setOutlineColor
    #if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 4
        text.setColor(sf::Color::Black);
    #else
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::Black);
    #endif

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