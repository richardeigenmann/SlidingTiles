#include "renderingSingleton.h"

const unsigned int WINDOW_WIDTH = 550;
const unsigned int WINDOW_HEIGHT = 400;
const unsigned int COLOR_DEPTH = 32;
const sf::String TITLE {"Sliding tiles"}; // NOLINT (fuchsia-statically-constructed-objects)
const unsigned int FRAME_RATE_LIMIT = 60;

SlidingTiles::RenderingSingleton::RenderingSingleton() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH), TITLE) { //NOLINT (fuchsia-default-arguments)
    window.setFramerateLimit(FRAME_RATE_LIMIT);
}

const int SlidingTiles::RenderingSingleton::tileSize;

sf::Vector2i SlidingTiles::RenderingSingleton::calculateCoordinates(sf::Vector2i xy) {
    return calculateCoordinates(xy.x, xy.y);
}

sf::Vector2i SlidingTiles::RenderingSingleton::calculateCoordinates(int x, int y) {
    sf::Vector2i coordinates = gridZeroZero;
    coordinates.x += x * tileSize;
    coordinates.y += y * tileSize;
    return coordinates;
}

sf::Vector2i SlidingTiles::RenderingSingleton::findTile(sf::Vector2i mousePosition) {
    sf::Vector2i gridCoordinates = mousePosition - gridZeroZero;
    if (gridCoordinates.x < 0 || gridCoordinates.y < 0
            || gridCoordinates.x > 4 * tileSize || gridCoordinates.y > 4 * tileSize) {
        return sf::Vector2i{-1, -1};
    }
    auto xPos = gridCoordinates.x / tileSize;
    auto yPos = gridCoordinates.y / tileSize;
    return sf::Vector2i{xPos, yPos};
}
