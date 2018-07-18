#include "movesLabel.h"

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
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::GAME_STARTED ) {
            moves = 0;
            updateLabel();
        } else if (state == ZmqSingleton::SLIDE_TILE ) {
            ++moves;
            updateLabel();
        }
    }
}

void MovesLabel::updateLabel() {
    std::ostringstream movesText;
    movesText << "Moves: " << moves;
    setText(movesText.str());
}