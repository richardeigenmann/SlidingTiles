#include "movesLabel.h"

using namespace SlidingTiles;
using json = nlohmann::json;

/**
 * @brief Constructor for the par Label
 */
MovesLabel::MovesLabel() {
    setPosition(400, 150);

    UpdatingSingleton::getInstance().add(*this);
    std::cout << "LevelLabel connecting to ZeroMQ socket: "
            << ZmqSingleton::RECEIVER_SOCKET << std::endl;
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

MovesLabel::~MovesLabel() {
    socket->close();
    UpdatingSingleton::getInstance().remove(*this);
}

void MovesLabel::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
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