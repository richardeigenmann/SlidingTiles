#pragma once
#include <string>

namespace SlidingTiles {

    /**
     * @brief The direction you can go
     */
    enum class Direction {
        Unknown, GoLeft, GoRight, GoUp, GoDown
    };

    auto directionToString(const Direction & direction) -> std::string;

    auto returnOppositeDirection(const Direction & direction) -> Direction;

}
