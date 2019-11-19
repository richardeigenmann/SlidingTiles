#pragma once
#include <iostream>
#include <string>
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "zmqSingleton.h"
#include "zmqSubscriber.h"

namespace SlidingTiles {
    /**
     * @brief A class to listen and log the messags passing through ZMQ.
     * We need to extend Updateable so that we can get invoked on every tick
     * and can use that invocation to check for new messages to retrieve and log.
     */
    class DebugMessageListener : public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for DebugMessageListener
         */
        explicit DebugMessageListener();

        /**
         * @brief Destructor for DebugMessageListener
         */
        ~DebugMessageListener();

        /**
         * @brief update callback
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

    };
}
