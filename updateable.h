#pragma once
#include "zmqSingleton.h"

namespace SlidingTiles {

    /**
     * @brief A class to extend which upon construction registers itself with the ZmqSingleton
     * and receives zmq messages in its virtual method update.
     */
    class Updateable {
    public:

        Updateable () {
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

        ~Updateable () {
            socket->close();
        }

        /**
         * @brief Implementing classes must define the update method
         */
        virtual void update(const float dt) = 0;

        /**
         * @brief The ZeroMQ socket of type subscriber. It is set by the 
         * constructor.
         */
        std::unique_ptr<zmq::socket_t> socket;


    private:
        /**
         * @brief A shared_ptr to the context of the ZeroMQ. It gets set by
         * the Constructor
         */
        std::shared_ptr<zmq::context_t> contextPtr;

    };
} // namespace SlidingTiles
