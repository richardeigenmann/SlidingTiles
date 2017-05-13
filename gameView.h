#pragma once
#include <SFML/Graphics.hpp>
#include "gameBoard.h"
#include "renderingSingleton.h"
#include "renderable.h"
#include "randomButton.h"
#include "nextButton.h"
#include "restartButton.h"
#include "attitudeSoundPlayer.h"

namespace SlidingTiles {

    /**
     * @brief The view class that ensures everything that needs to be shown in shown
     */
    class GameView : public Renderable {
    public:
        /**
         * @brief constructor for the view of the game
         */
        GameView();

        /**
         * @brief knows how to render the game
         */
        void render() override;

        /**
         * Overrides the renderable priority to clear the background
         * @return the RenderPriorits Background
         */
        Renderable::RenderPriority getRenderPriority() override;

        /**
         * @brief pointer to the gameBoard
         */
        SlidingTiles::GameBoard* gameBoard;

        /**
         * @brief set the Game Board
         */
        void setGameBoard(SlidingTiles::GameBoard * gB) {
            gameBoard = gB;
        }

    private:
        /**
         * @brief a vector to hold the unique_ptr to the TileView objects
         */
        std::vector<std::unique_ptr<TileView>> tileViews;
        
                /**
         * a Button for a random level
         */
        RandomButton randomSfmlButton{};
        
        /**
         * a Button to go to the next level
         */
        NextButton nextSfmlButton{};
        /**
         * a restart button
         */
        RestartButton restartSfmlButton{};

        /**
         * Add the AttitudeSoundPlayer
         */
        AttitudeSoundPlayer AttitudeSoundPlayer{};

    };

} // namespace SlidingTiles
