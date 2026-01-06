#pragma once
#include "button.h"
#include "strongTypes.h"

namespace SlidingTiles {

    /**
     * @brief A button showing the undo icon
     */
    class UndoButton : public Button {
    public:

        /**
         * @brief Constructor for the undo button
         */
        explicit UndoButton() : Button(AssetPath{"undo.png"}, ZmqSingleton::UNDO_MOVE) {
            isVisible = false;
            setPosition(430, 350);
            getSprite().setScale(0.4f, 0.4f);
        }

        void handleMessage(const nlohmann::json & jsonMessage) override {
            Button::handleMessage(jsonMessage);
            auto state = jsonMessage["state"].get<std::string>();
            if (state == SlidingTiles::ZmqSingleton::BROADCAST_MOVES_COUNT) {
                countMoves = jsonMessage["count"].get<size_t>();
                isVisible = countMoves > 0;
            }
        }

    private:
        size_t countMoves {0};

    };
}
