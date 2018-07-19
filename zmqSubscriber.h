#pragma once
#include "zmqSingleton.h"
#include <experimental/optional>

namespace SlidingTiles {

    /**
     * @brief A class to extend which upon construction registers itself with the ZmqSingleton
     * and can then pick up zmq messages in its virtual method update.
     */
    class ZmqSubscriber {
    public:

        ZmqSubscriber () {
            contextPtr = ZmqSingleton::getInstance().getContext();
            try {
                socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
                socket->connect(ZmqSingleton::RECEIVER_SOCKET);
                socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
            } catch (const zmq::error_t & e) {
                throw std::runtime_error("ZeroMQ Error when connecting LevelLabel to socket "
                        + ZmqSingleton::RECEIVER_SOCKET + ": " + e.what());
            }
        }

        ~ZmqSubscriber () {
            socket->close();
        }

        /**
         * @brief The ZeroMQ socket of type subscriber. It is set by the 
         * constructor.
         */
        std::unique_ptr<zmq::socket_t> socket;

        /**
         * @brief returns the zmq message if one is pending. 
         * Call this periodically and test if it is true.
         * @return a std::optional with the json object that was found
         */
        std::experimental::optional<json> getZmqMessage() {
            zmq::message_t reply;
            if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
                std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
                return  json::parse(message);
            } 
            return {};
        }


    private:
        /**
         * @brief A shared_ptr to the context of the ZeroMQ. It gets set by
         * the Constructor
         */
        std::shared_ptr<zmq::context_t> contextPtr;

    };
} // namespace SlidingTiles
