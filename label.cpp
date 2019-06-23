#include "label.h"

const sf::String FONT_FILE {"sliding-tiles-assets/Raleway-Regular.ttf"}; //NOLINT (fuchsia-statically-constructed-objects, fuchsia-default-arguments, cert-err58-cpp)
const unsigned int FONT_SIZE {16};

SlidingTiles::Label::Label() {
    if (!font.loadFromFile(FONT_FILE)) {
        std::cout << "Can't load font " << FONT_FILE.toAnsiString() << std::endl; //NOLINT (fuchsia-default-arguments)
    }

    text.setFont(font);
    text.setCharacterSize(FONT_SIZE);

    // Travis uses an old Ubuntu that only has SFML 2.1 which doesn't have setFillColor and setOutlineColor
    #if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 4
        text.setColor(sf::Color::Black);
    #else
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::Black);
    #endif

    SlidingTiles::RenderingSingleton::getInstance().add(*this);
}

void SlidingTiles::Label::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void SlidingTiles::Label::setText(const std::string & newText) {
    text.setString(newText); // NOLINT (fuchsia-default-arguments)
}

void SlidingTiles::Label::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(text); // NOLINT (fuchsia-default-arguments)
}