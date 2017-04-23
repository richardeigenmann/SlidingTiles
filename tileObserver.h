#pragma once

#include <SFML/Graphics.hpp>
#include "tileView.h"
#include "direction.h"
#include "tileType.h"

namespace SlidingTiles {

    /**
     * @brief Interface that defines what a TileObserver must implement
     */
    class TileObserver {
    public:

        /**
         * @brief Update event
         * @param dt The delta time in seconds
         */
        virtual void update(const float dt) = 0;
        
        /**
         * @brief Render event
         */
        virtual void render() = 0;
        
        /**
         * @brief settor for the tile type
         * @param newType the new type of the tile.
         */
        virtual void setTileType(const TileType & newType) = 0;

        /**
         * @brief settor for the tile coordinates in game coordinates
         */
        virtual void setCoordinates(const sf::Vector2i & newGameBoardPosition) = 0;
        
        /**
         * @brief starts a transition to the supplied new game coordinates
         */
        virtual void transition(const sf::Vector2i & newGameBoardPosition) = 0;

        /**
         * @brief settor for the winner flag
         */
        virtual void setWinner(const bool & status) = 0;
    };

} // namespace SlidingTiles
