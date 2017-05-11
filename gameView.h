#pragma once
#include <SFML/Graphics.hpp>
#include "gameBoard.h"
#include "renderingSingleton.h"
#include "renderable.h"

namespace SlidingTiles {

    /**
     * @brief The view class for the tile that knows how to render itself
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

    };

} // namespace SlidingTiles
