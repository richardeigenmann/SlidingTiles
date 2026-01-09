#pragma once
#include "zmqSingleton.h"
#include <optional>

namespace SlidingTiles {

    /**
     * @brief A class to extend which upon construction registers itself with the ZmqSingleton
     * and can then pick up zmq messages in its virtual method update.
     */
    class ZmqSubscriber {
    public:

        explicit ZmqSubscriber () {
            contextPtr = ZmqSingleton::getInstance().getContext();
            try {
                socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
                socket->connect(std::string(ZmqSingleton::RECEIVER_SOCKET));
                socket->set(zmq::sockopt::subscribe, "");
            } catch (const zmq::error_t & e) {
                throw std::runtime_error("ZeroMQ Error when connecting LevelLabel to socket "
                        + std::string(ZmqSingleton::RECEIVER_SOCKET) + ": " + e.what());
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
         * @return a std::optional with the JSON object that was found
         */
        std::optional<json> getZmqMessage() {
            zmq::message_t reply;
            if ( socket != nullptr ) {
                auto result = socket->recv(reply, zmq::recv_flags::dontwait);
                if ( result ) {
                    std::string_view msg_view(static_cast<const char*>(reply.data()), reply.size());
                    try {
                        return json::parse(msg_view);
                    } catch (const json::parse_error& e) {
                        return std::nullopt;
                    }
                }
            } 
            return std::nullopt;
        }


    private:
        /**
         * @brief A shared_ptr to the context of the ZeroMQ. It gets set by
         * the Constructor
         */
        std::shared_ptr<zmq::context_t> contextPtr;

    };
} // namespace SlidingTiles
