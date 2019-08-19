#pragma once
#include "button.h"

namespace SlidingTiles {

    /**
     * @brief A button showing the undo icon
     */
    class UndoButton : public Button {
    public:

        /**
         * @brief Constructor for the undo button
         */
        explicit UndoButton() : Button("undo.png", ZmqSingleton::UNDO_MOVE) {
            setPosition(430, 350);
            getSprite().setScale(0.4f, 0.4f);
        };

    };
}
