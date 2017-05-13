#pragma once

#include "button.h"

namespace SlidingTiles {

    /**
     * @brief A base button showing Random on it
     */
    class RandomButton : public Button {
    public:

        /**
         * @brief Constructor for the button with Random on it
         */
        RandomButton() : Button("assets/button_random.png", ZmqSingleton::LOAD_RANDOM_LEVEL) {
            setPosition(400, 230);
        };

    };
}
