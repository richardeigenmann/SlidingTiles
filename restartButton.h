#pragma once

#include "button.h"

namespace SlidingTiles {

    /**
     * @brief A base button showing Random on it
     */
    class RestartButton : public Button {
    public:

        /**
         * @brief Constructor for the button with Random on it
         */
        explicit RestartButton() : Button("button_restart.png", ZmqSingleton::RESTART_LEVEL) {
            setPosition(400, 310);
        };

    };
}