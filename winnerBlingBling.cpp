#include "winnerBlingBling.h"
#include "renderingSingleton.h"
#include <iostream>

using namespace SlidingTiles;

WinnerBlingBling::WinnerBlingBling() {
    const std::string filename{"assets/trophy.png"};
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    setPosition(400, 5);
    sprite.setScale(0.2f, 0.2f);
}

void WinnerBlingBling::loadSounds(const json & jsonArray) {
    winnerSounds.loadSounds(jsonArray);
}

void WinnerBlingBling::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

/**
 * @brief call this to start the bling bling
 * @param time The amount of time it will last
 */
void WinnerBlingBling::startBlingBling(const float & time, std::size_t moves, std::size_t par) {
    if ( moves == par ) {
        winnerSounds.playRandomSound();
    } else {
        winnerSounds.playRandomSound();
    }
}

void WinnerBlingBling::update(const float & dt) {
}

void WinnerBlingBling::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}

