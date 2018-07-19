#include "levelLabel.h"
#include "json.hpp"
#include <sstream>

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
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void LevelLabel::handleMessage(const json & jsonMessage) {
    std::string state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::GAME_STARTED) {
        int level = jsonMessage["level"];
        setLevel( level );
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