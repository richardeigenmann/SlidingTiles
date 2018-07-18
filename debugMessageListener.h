#pragma once
#include <iostream>
#include <string>
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "zmqSingleton.h"

namespace SlidingTiles {
    /**
     * @brief A base button class
     */
    class DebugMessageListener : public Updateable {
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
    };
}
