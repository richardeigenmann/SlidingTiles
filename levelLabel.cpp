#include "levelLabel.h"

using namespace SlidingTiles;
using json = nlohmann::json;

/**
 * @brief Constructor for the level Label
 */
LevelLabel::LevelLabel() {
    setPosition(400, 120);

    UpdatingSingleton::getInstance().add(*this);
    contextPtr = ZmqSingleton::getInstance().getContext();
    try {
        socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
        socket->connect(ZmqSingleton::RECEIVER_SOCKET);
        socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when connecting LevelLabel to socket "
                + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
    }
};

LevelLabel::~LevelLabel() {
    socket->close();
    UpdatingSingleton::getInstance().remove(*this);
}

void LevelLabel::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::GAME_STARTED) {
            int level = jsonMessage["level"];
            std::cout << "loading level " << level << std::endl;
            std::ostringstream levelText;
            levelText << "Level: " << level;
            setText(levelText.str());
        }
    }
}