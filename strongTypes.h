#pragma once

#include <string>

namespace SlidingTiles {

    struct AssetPath {
        std::string value;
        // Allows passing a string literal directly to the struct
        explicit AssetPath(std::string v) : value(std::move(v)) {}
    };

} // namespace SlidingTiles