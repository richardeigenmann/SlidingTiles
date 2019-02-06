#include "direction.h"

std::string SlidingTiles::directionToString(const Direction & direction) {
    if (direction == Direction::GoDown) {
        return "GoDown";
    }
    if (direction == Direction::GoRight) {
        return "GoRight";
    }
    if (direction == Direction::GoUp) {
        return "GoUp";
    }
    if (direction == Direction::GoLeft) {
        return "GoLeft";
    }
    return "Unknown";
}
