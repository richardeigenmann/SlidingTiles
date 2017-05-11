#include "winnerBlingBling.h"

using namespace SlidingTiles;

WinnerBlingBling::WinnerBlingBling() {
    const std::string filename{"assets/trophy.png"};
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    setPosition(400, 5);
    sprite.setScale(0.2f, 0.2f);
    RenderingSingleton::getInstance().add(*this);
    UpdatingSingleton::getInstance().add(*this);

    //std::cout << "WinnerBlingBling connecting to ZeroMQ socket: " << PublishingSingleton::RECEIVER_SOCKET << std::endl;
    socket.connect(PublishingSingleton::RECEIVER_SOCKET);
    socket.setsockopt(ZMQ_SUBSCRIBE, 0, 0);
}

WinnerBlingBling::~WinnerBlingBling() {
    socket.close();
    RenderingSingleton::getInstance().remove(*this);
    UpdatingSingleton::getInstance().remove(*this);
}

void WinnerBlingBling::loadSounds(const json & jsonArray) {
    winnerSounds.loadSounds(jsonArray);
}

void WinnerBlingBling::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void WinnerBlingBling::startBlingBling(const float & time, std::size_t moves, std::size_t par) {
    if (moves == par) {
        winnerSounds.playRandomSound();
    } else {
        winnerSounds.playRandomSound();
    }
    gameState = GameState::VictoryRolling;
}

void WinnerBlingBling::endBlingBling() {
    gameState = GameState::Playing;
}

void WinnerBlingBling::update(const float dt) {
    zmq::message_t reply;
    if (socket.recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        //std::cout << "WinnerBlingBling received: " << message << std::endl;
        auto j = json::parse(message);
        std::string state = j["state"].get<std::string>();
        if (state == PublishingSingleton::GAME_WON) {
            startBlingBling(j["victoryRollTime"], j["moves"], j["par"]);
        } else if (state == PublishingSingleton::GAME_STARTED) {
            endBlingBling();
        }
    }
}

void WinnerBlingBling::render() {
    if (gameState == GameState::VictoryRolling) {
        RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
    }
}

