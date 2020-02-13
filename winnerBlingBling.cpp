#include "winnerBlingBling.h"
#include "executablePath.h"

SlidingTiles::WinnerBlingBling::WinnerBlingBling() noexcept(false) {
    const std::string filename{getAssetDir() + "trophy.png"};
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    const unsigned int X {400};
    const unsigned int Y {5};
    const float SCALE {0.2F};
    setPosition(X, Y);
    sprite.setScale(SCALE, SCALE);
    RenderingSingleton::getInstance().add(*this);
    UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::WinnerBlingBling::~WinnerBlingBling() {
    RenderingSingleton::getInstance().remove(*this);
    UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::WinnerBlingBling::loadSounds(const json & jsonArray) {
    winnerSounds.loadSounds(jsonArray);
}

void SlidingTiles::WinnerBlingBling::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void SlidingTiles::WinnerBlingBling::startBlingBling(std::size_t moves, std::size_t par) {
    if (moves == par) {
        winnerSounds.playRandomSound();
    }
    gameState = GameState::VictoryRolling;
}

void SlidingTiles::WinnerBlingBling::endBlingBling() {
    gameState = GameState::Playing;
}

void SlidingTiles::WinnerBlingBling::update(const float dt) { // NOLINT (misc-unused-parameters)
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void SlidingTiles::WinnerBlingBling::handleMessage(const json & jsonMessage) {
    auto state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::CONFIGURATION_LOADED) {
        loadSounds(jsonMessage["winnerSoundBites"]);
    } else if (state == SlidingTiles::ZmqSingleton::GAME_WON) {
        startBlingBling(jsonMessage["moves"], jsonMessage["par"]);
    } else if (state == SlidingTiles::ZmqSingleton::GAME_STARTED) {
        endBlingBling();
    }
}

void SlidingTiles::WinnerBlingBling::render() {
    if (gameState == GameState::VictoryRolling) {
        SlidingTiles::RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
    }
}

