#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

namespace SlidingTiles {

    /**
     * @brief A Move of a tile
     */
    class Move {
    public:

        /**
         * @brief A single step move for a tile at the supplied position in the
         * supplied direction
         * @param startPosition the game board coordinates of the moving tile
         * @param direction the direction to move in
         */
        explicit Move(const sf::Vector2<int> & startPosition, const SlidingTiles::Direction & direction)
        : startPosition(startPosition), direction(direction) {
        };

        /**
         * @brief the game board coordinates of the moving tile
         */
        sf::Vector2<int> startPosition;

        /**
         * @brief the direction we are moving in
         */
        SlidingTiles::Direction direction;

        /**
         * @brief explains the move
         */
        virtual std::string toString() {
            std::stringstream ss;
            ss << "Move startPosition: [" << startPosition.x << "][" << startPosition.y << "]";
            ss << " direction: " << directionToString(direction) << "\n";
            return ss.str();
        }

        /**
         * @brief explains the move
         */
        friend std::ostream& operator<< (std::ostream& os, const SlidingTiles::Move& move) {
            os << "Move startPosition: [" << move.startPosition.x << "][" << move.startPosition.y << "]";
            os << " direction: " << directionToString(move.direction) << "\n";
            return os;
        }

    };

} // namespace SlidingTiles
