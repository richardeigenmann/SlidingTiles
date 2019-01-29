#pragma once
#include <string>

namespace SlidingTiles {

    /**
     * @brief The direction you can go
     */
    enum class Direction {
        Unknown, GoLeft, GoRight, GoUp, GoDown
    };

    std::string directionToString(const Direction & direction);

}
