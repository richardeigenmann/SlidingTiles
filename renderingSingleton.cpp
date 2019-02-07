#include "renderingSingleton.h"

using namespace SlidingTiles;

RenderingSingleton::RenderingSingleton() : window(sf::VideoMode(550, 400, 32), "Sliding tiles") {
    window.setFramerateLimit(60);
}

const int RenderingSingleton::tileSize;

sf::Vector2i RenderingSingleton::calculateCoordinates(sf::Vector2i xy) {
    return calculateCoordinates(xy.x, xy.y);
}

sf::Vector2i RenderingSingleton::calculateCoordinates(int x, int y) {
    sf::Vector2i coordinates = gridZeroZero;
    coordinates.x += x * tileSize;
    coordinates.y += y * tileSize;
    return coordinates;
}

sf::Vector2i RenderingSingleton::findTile(sf::Vector2i mousePosition) {
    sf::Vector2i gridCoordinates = mousePosition - gridZeroZero;
    if (gridCoordinates.x < 0 || gridCoordinates.y < 0
            || gridCoordinates.x > 4 * tileSize || gridCoordinates.y > 4 * tileSize) {
        return sf::Vector2i{-1, -1};
    }
    auto xPos = gridCoordinates.x / tileSize;
    auto yPos = gridCoordinates.y / tileSize;
    return sf::Vector2i{xPos, yPos};
}
