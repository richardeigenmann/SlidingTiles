#include "direction.h"
#include <string>

auto SlidingTiles::directionToString(const Direction &direction)
    -> std::string {
  switch (direction) {
  case Direction::GoDown:
    return "GoDown";
    break;
  case Direction::GoRight:
    return "GoRight";
    break;
  case Direction::GoUp:
    return "GoUp";
    break;
  case Direction::GoLeft:
    return "GoLeft";
    break;
  default:
    return "Unknown";
  }
}

auto SlidingTiles::returnOppositeDirection(const Direction &direction)
    -> Direction {
  switch (direction) {
  case Direction::GoDown:
    return Direction::GoUp;
    break;
  case Direction::GoRight:
    return Direction::GoLeft;
    break;
  case Direction::GoUp:
    return Direction::GoDown;
    break;
  case Direction::GoLeft:
    return Direction::GoRight;
    break;
  default:
    return Direction::Unknown;
  }
}
