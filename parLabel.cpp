#include "parLabel.h"
#include <sstream>

using json = nlohmann::json;

const unsigned int X {400};
const unsigned int Y {180};

/**
 * @brief Constructor for the par label
 */
SlidingTiles::ParLabel::ParLabel() {
    setPosition(X, Y);

    UpdatingSingleton::getInstance().add(*this);
};

SlidingTiles::ParLabel::~ParLabel() {
    UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::ParLabel::update(const float dt) { //NOLINT (misc-unused-parameters)
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void SlidingTiles::ParLabel::handleMessage(const json & jsonMessage) {
    auto state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::GAME_STARTED) {
        int par = jsonMessage["par"];
        std::ostringstream parText;
        parText << "Par: " << par;
        setText(parText.str());
    }
}