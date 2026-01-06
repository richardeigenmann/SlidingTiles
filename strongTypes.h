#ifndef SLIDING_TILES_STRONGTYPES_H
#define SLIDING_TILES_STRONGTYPES_H

#include <string>

namespace SlidingTiles {

    struct AssetPath {
        std::string value;
        // Allows passing a string literal directly to the struct
        explicit AssetPath(std::string v) : value(std::move(v)) {}
    };

} // namespace SlidingTiles

#endif //SLIDING_TILES_STRONGTYPES_HD