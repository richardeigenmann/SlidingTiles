#include "parLabel.h"

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
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::GAME_STARTED) {
            int par = jsonMessage["par"];
            std::ostringstream parText;
            parText << "Par: " << par;
            setText(parText.str());
        }
    }
}