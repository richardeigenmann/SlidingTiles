#pragma once
#include <cstddef> // Required for std::size_t

namespace SlidingTiles {
    struct GameSettings {
        std::size_t emptyTiles;
        std::size_t maxDepth;
    };
} // namespace SlidingTiles
