#pragma once

namespace SlidingTiles {

    /**
     * @brief Interface that defines what a Updateable must implement
     */
    class Updateable {
    public:

        /**
         * @brief Implementing classes must define the update method
         */
        virtual void update(const float dt) = 0;

    };

} // namespace SlidingTiles
