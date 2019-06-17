#include "direction.h"

std::string SlidingTiles::directionToString(const Direction & direction) {
    switch (direction) {
        // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
        case Direction::GoDown: return "GoDown"; break;
        // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
        case Direction::GoRight: return "GoRight"; break;
        // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
        case Direction::GoUp: return "GoUp"; break;
        // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
        case Direction::GoLeft: return "GoLeft"; break;
        // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
        default: return "Unknown";
    }
}
