#include "movesLabel.h"
#include <sstream>

using namespace SlidingTiles;
using json = nlohmann::json;

/**
 * @brief Constructor for the moves label
 */
MovesLabel::MovesLabel() {
    setPosition(400, 150);

    UpdatingSingleton::getInstance().add(*this);
};

MovesLabel::~MovesLabel() {
    UpdatingSingleton::getInstance().remove(*this);
}

void MovesLabel::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void MovesLabel::handleMessage(const json & jsonMessage) {
    std::string state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::GAME_STARTED ) {
        moves = 0;
        updateLabel();
    } else if (state == ZmqSingleton::SLIDE_TILE ) {
        ++moves;
        updateLabel();
    }
}

void MovesLabel::updateLabel() {
    std::ostringstream movesText;
    movesText << "Moves: " << moves;
    setText(movesText.str());
}