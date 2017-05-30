#include "button.h"
#include <iostream>


using namespace SlidingTiles;
using json = nlohmann::json;

Button::Button(const std::string & filename, const std::string & command) : command(command) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    } else {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    RenderingSingleton::getInstance().add(*this);

    UpdatingSingleton::getInstance().add(*this);

    std::cout << "DebugMessageListener connecting to ZeroMQ socket: "
            << ZmqSingleton::RECEIVER_SOCKET << std::endl;
    contextPtr = ZmqSingleton::getInstance().getContext();
    try {
        socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
        socket->connect(ZmqSingleton::RECEIVER_SOCKET);
        socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
    } catch (const zmq::error_t & e) {
        throw std::runtime_error("ZeroMQ Error when connecting Button to socket "
                + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
    }
}

/**
 * @brief Destructor
 */
Button::~Button() {
    RenderingSingleton::getInstance().remove(*this);
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Button::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}

bool Button::mouseReleased(const sf::Vector2i & mousePosition) {
    return sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void Button::update(const float dt) {
    zmq::message_t reply;
    if (socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        auto jsonMessage = json::parse(message);
        std::string state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::MOUSE_CLICKED) {
            int x = jsonMessage["x"];
            int y = jsonMessage["y"];
            if (mouseReleased(sf::Vector2i{x, y})) {
                json commandMessage{};
                commandMessage["state"] = command;
                ZmqSingleton::getInstance().publish(commandMessage);
            }
        }
    }
}
