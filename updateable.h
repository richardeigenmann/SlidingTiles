#pragma once
#include "zmqSingleton.h"
#include <experimental/optional>

namespace SlidingTiles {

    /**
     * @brief An interface to define that implementing classes need to 
     * override the virtual method update to receive the execution thread
     * to do periodic stuff.
     */
    class Updateable {
    public:
        /**
         * @brief Implementing classes must define the update method
         */
        virtual void update(const float dt) = 0;
    };
} // namespace SlidingTiles
