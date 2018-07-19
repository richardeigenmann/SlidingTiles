#pragma once
#include <iostream>
#include <string>
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "zmqSingleton.h"
#include "zmqSubscriber.h"

namespace SlidingTiles {
    /**
     * @brief A base button class
     */
    class DebugMessageListener : public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for DebugMessageListener
         */
        DebugMessageListener();

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
