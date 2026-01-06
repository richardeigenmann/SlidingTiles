#pragma once

#include "button.h"
#include "strongTypes.h"

namespace SlidingTiles {

    /**
     * @brief A base button showing Random on it
     */
    class NextButton : public Button {
    public:

        /**
         * @brief Constructor for the button with Random on it
         */
        explicit NextButton() : Button(AssetPath{"button_next.png"}, ZmqSingleton::LOAD_NEXT_LEVEL) {
            setPosition(400, 270);
        };

    };
}