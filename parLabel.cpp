#include "parLabel.h"
#include <sstream>

using namespace SlidingTiles;
using json = nlohmann::json;

/**
 * @brief Constructor for the par label
 */
ParLabel::ParLabel() {
    setPosition(400, 180);

    UpdatingSingleton::getInstance().add(*this);
};

ParLabel::~ParLabel() {
    UpdatingSingleton::getInstance().remove(*this);
}

void ParLabel::update(const float dt) {
    auto msg = getZmqMessage();
    if (msg) {
        handleMessage(msg.value());
    }
}

void ParLabel::handleMessage(const json & jsonMessage) {
    std::string state = jsonMessage["state"].get<std::string>();
    if (state == ZmqSingleton::GAME_STARTED) {
        int par = jsonMessage["par"];
        std::ostringstream parText;
        parText << "Par: " << par;
        setText(parText.str());
    }
}