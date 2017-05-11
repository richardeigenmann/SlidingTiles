#pragma once

#include <SFML/Graphics.hpp>
#include "tileView.h"
#include "direction.h"
#include "tileType.h"

namespace SlidingTiles {

    /**
     * @brief A tile on the board
     */
    class Tile {
    public:
        /**
         * @brief sets the tile position to the supplied game board position
         */
        void setTilePosition(const sf::Vector2i & newGameBoardPosition) {
            myPosition = newGameBoardPosition;
            /*for (auto& pair : tileObservers) {
                pair.second->setCoordinates(newGameBoardPosition);
            }*/
        }

        /**
         * Update event
         * @param dt The delta time in seconds
         *
        void update(const float dt) {
            for (auto& pair : tileObservers) {
                pair.second->update(dt);
            }*/

        /**
         * @brief returns the tile position
         * @return The position in the gameboard
         */
        sf::Vector2i getTilePosition() {
            return myPosition;
        }

        /**
         * @brief tells the tile to transition to a new position in game board coordinates
         */
        void transition(const sf::Vector2i & newGameBoardPosition);

        /**
         * @brief sets the tile type
         */
        void setTileType(const TileType & newType);

        /**
         * @brief sets the tile type as per the character convention
         */
        void setTileType(const std::string & c);

        /**
         * @brief sets the tile type as per the character convention
         */
        void setTileType(const std::wstring & c);

        /**
         * @brief Returns the type of the tile
         */
        TileType getTileType() {
            return tileType;
        };

        /**
         * @brief returns if a tile is moveable
         */
        bool isMoveable{false};

        /**
         * @brief returns the Direction that we come out of a tile in if
         * we enter it in the incomingDirection
         * @param incomingDirection the incoming direction
         */
        Direction outputDirection(const Direction & incomingDirection);

        /**
         * @brief settor for the winner flag
         */
        void setWinner(const bool & status);

        /**
         * @brief gettor for the winner flag
         */
        bool isWinner() {
            return winner;
        }

        /**
         * Adds a TileObserver to the tile that will then get notified when
         * interesting things happen on the tile.
         * @param tileObserver The object that wants to find out about tile events
         *
        void add(TileObserver& tileObserver) {
            tileObservers.insert(std::pair<TileObserver * const, TileObserver * const>(&tileObserver, &tileObserver));
        }*/

        /**
         * Removes a TileObserver object from the list of notified objects
         * @param tileObserver
         *
        void remove(TileObserver& tileObserver) {
            tileObservers.erase(&tileObserver);
        }*/

    private:
        /**
         * @brief The type of the tile
         */
        TileType tileType{TileType::Empty};

        /**
         * @brief sets the isMoveable flag based on the type of tile
         */
        void setMoveable(const TileType & newType);

        /**
         * @brief a bool to tell us if the tile is part of the solution path or not
         */
        bool winner{false};

        /**
         * @brief the game board position of the tile
         */
        sf::Vector2i myPosition{-1, -1};

        /**
         * @brief The map of TileOberservers
         */
        //std::map<TileObserver * const, TileObserver * const> tileObservers;
    };

} // namespace SlidingTiles
