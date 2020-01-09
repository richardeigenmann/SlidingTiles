#pragma once
#include "button.h"
#include "zmqSubscriber.h"

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
            isVisible = false;
            setPosition(430, 350);
            getSprite().setScale(0.4f, 0.4f);
        }

        void handleMessage(const nlohmann::json & jsonMessage) override {
            Button::handleMessage(jsonMessage);
            auto state = jsonMessage["state"].get<std::string>();
            if (state == SlidingTiles::ZmqSingleton::GAME_STARTED) {
                isVisible = false;
                countMoves = 0;
            } else if (state == SlidingTiles::ZmqSingleton::SLIDE_TILE) {
                isVisible = true;
                ++countMoves;
            } else if (state == SlidingTiles::ZmqSingleton::UNDO_MOVE) {
                if ( countMoves > 0 ) {
                    --countMoves;
                } 
                if ( countMoves == 0 ) {
                    isVisible = false;
                }
            }
        }

    private:
        size_t countMoves {0};

    };
}
