#include "direction.h"
#include <gmock/gmock.h>

using namespace SlidingTiles;

TEST(Direction, Unkonwn) {
    Direction d = Direction::Unknown;
    ASSERT_EQ("Unknown", directionToString(d));
}

TEST(Direction, GoDown) {
    Direction d = Direction::GoDown;
    ASSERT_EQ("GoDown", directionToString(d));
}

TEST(Direction, GoUp) {
    Direction d = Direction::GoUp;
    ASSERT_EQ("GoUp", directionToString(d));
}

TEST(Direction, GoLeft) {
    Direction d = Direction::GoLeft;
    ASSERT_EQ("GoLeft", directionToString(d));
}

TEST(Direction, GoRight) {
    Direction d = Direction::GoRight;
    ASSERT_EQ("GoRight", directionToString(d));
}

TEST(Direction, undoGoRight) {
    Direction d = Direction::GoRight;
    Direction undoDirection = returnOppositeDirection(d);
    ASSERT_EQ(Direction::GoLeft, undoDirection);
}

TEST(Direction, undoGoLeft) {
    Direction d = Direction::GoLeft;
    Direction undoDirection = returnOppositeDirection(d);
    ASSERT_EQ(Direction::GoRight, undoDirection);
}

TEST(Direction, undoGoUp) {
    Direction d = Direction::GoUp;
    Direction undoDirection = returnOppositeDirection(d);
    ASSERT_EQ(Direction::GoDown, undoDirection);
}


TEST(Direction, undoGoDown) {
    Direction d = Direction::GoDown;
    Direction undoDirection = returnOppositeDirection(d);
    ASSERT_EQ(Direction::GoUp, undoDirection);
}