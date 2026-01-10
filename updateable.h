#pragma once

#include <SFML/System/Time.hpp>

namespace SlidingTiles {

    /**
     * @brief An interface to define that implementing classes need to 
     * override the virtual method update to receive the execution thread
     * to do periodic stuff.
     */
    class Updateable {
    public:
        // Always include a virtual destructor for interfaces!
        virtual ~Updateable() = default;

        /**
         * @brief Implementing classes must define the update method
         */
        virtual void update(const sf::Time deltaTime) = 0;
    };
} // namespace SlidingTiles
