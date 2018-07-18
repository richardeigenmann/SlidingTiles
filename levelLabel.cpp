#include "levelLabel.h"
#include "json.hpp"

using namespace SlidingTiles;
using json = nlohmann::json;

/**
 * @brief Constructor for the level Label
 */
LevelLabel::LevelLabel() {
    setPosition(400, 120);

    UpdatingSingleton::getInstance().add(*this);
};

LevelLabel::~LevelLabel() {
    UpdatingSingleton::getInstance().remove(*this);
}

/**
 * Listens for the ZmqSingleton::GAME_STARTED message and updates the level label
 */
void LevelLabel::update(const float dt) {
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::GAME_STARTED) {
            int level = jsonMessage["level"];
            setLevel( level );
        }
    }
}

/**
 * sets the label to the text Level: n 
 */
void LevelLabel::setLevel( int level ) {
    std::ostringstream levelText;
    levelText << "Level: " << level;
    setText(levelText.str());

}