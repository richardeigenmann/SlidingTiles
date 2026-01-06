#pragma once

#include "gameBoard.h"
#include "renderable.h"
#include "randomButton.h"
#include "nextButton.h"
#include "restartButton.h"
#include "attitudeSoundPlayer.h"
#include "levelLabel.h"
#include "parLabel.h"
#include "movesLabel.h"
#include "undoButton.h"

namespace SlidingTiles {

    /**
     * @brief The view class that ensures everything that needs to be shown in shown
     */
    class GameView : public Renderable {
    public:
        /**
         * @brief constructor for the view of the game
         */
        explicit GameView();

        /**
         * @brief knows how to render the game
         */
        void render() override;

        /**
         * Overrides the renderable priority to clear the background
         * @return the RenderPriorits Background
         */
        Renderable::RenderPriority getRenderPriority() const override;

        /**
         * @brief pointer to the gameBoard
         */
        GameBoard* gameBoard {nullptr};

        /**
         * @brief set the Game Board
         */
        void setGameBoard(GameBoard * gB) {
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
        std::unique_ptr<RandomButton> randomSfmlButton{};

        /**
         * a Button to go to the next level
         */
        std::unique_ptr<NextButton> nextSfmlButton{};
        /**
         * a restart button
         */
        std::unique_ptr<RestartButton> restartSfmlButton{};

        /**
         * Add the Undo Button
        */
        std::unique_ptr<UndoButton> undoButton{};

        /**
         * Add the AttitudeSoundPlayer
         */
        std::unique_ptr<AttitudeSoundPlayer> attitudeSoundPlayer{};

        /**
         * Add the LevelLabel
         */
        std::unique_ptr<LevelLabel> levelLabel{};

        /**
         * Add the ParLabel
         */
        std::unique_ptr<ParLabel> parLabel{};
        
        /**
         * Add the MovesLabel
         */
        std::unique_ptr<MovesLabel> movesLabel{};


    };

} // namespace SlidingTiles
