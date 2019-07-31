#include "overPar.h"

SlidingTiles::OverPar::OverPar() {
    const std::string filename{RenderingSingleton::getInstance().getAssetDir() + "over_par.png"}; // NOLINT (fuchsia-default-arguments)
    if (texture.loadFromFile(filename)) { // NOLINT (fuchsia-default-arguments)
        sprite.setTexture(texture); // NOLINT (fuchsia-default-arguments)
    } else {
        throw std::runtime_error("Failed to load texture: " + filename); // NOLINT (fuchsia-default-arguments)
    }
    const unsigned int X {410};
    const unsigned int Y {20};
    const float SCALE {0.2F};
    setPosition(X, Y);
    sprite.setScale(SCALE, SCALE);
    RenderingSingleton::getInstance().add(*this);
    UpdatingSingleton::getInstance().add(*this);
}

SlidingTiles::OverPar::~OverPar() {
    RenderingSingleton::getInstance().remove(*this);
    UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::OverPar::loadSounds(const json & jsonArray) {
    overParSounds.loadSounds(jsonArray);
}

void SlidingTiles::OverPar::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}

void SlidingTiles::OverPar::startOverPar() {
    gameState = GameState::OverPar;
    overParSounds.playRandomSound();
}

void SlidingTiles::OverPar::endOverPar() {
    gameState = GameState::VictoryRolling;
}

void SlidingTiles::OverPar::update(const float dt) { // NOLINT (misc-unused-parameters)
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void SlidingTiles::OverPar::handleMessage(const json & jsonMessage) {
    auto state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::CONFIGURATION_LOADED) {
        loadSounds(jsonMessage["attitudeSoundBites"]);
    } else if (state == SlidingTiles::ZmqSingleton::GAME_WON) {
        endOverPar();
    } else if (state == SlidingTiles::ZmqSingleton::OVER_PAR) {
        startOverPar();
    }
}

void SlidingTiles::OverPar::render() {
    if (gameState == GameState::OverPar) {
        SlidingTiles::RenderingSingleton::getInstance().getRenderWindow()->draw(sprite); // NOLINT (fuchsia-default-arguments)
    }
}

