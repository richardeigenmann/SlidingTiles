#include "move.h"
#include <gmock/gmock.h>

using namespace::testing;
using namespace SlidingTiles;

TEST(Move, Constructor) {
    Move move{sf::Vector2i{0, 1}, Direction::GoRight};
    ASSERT_THAT(move.startPosition.x, 0);
    ASSERT_THAT(move.startPosition.y, 1);
    ASSERT_THAT(move.direction, Direction::GoRight);
}

TEST(Move, toString) {
    Move move{sf::Vector2i{0, 1}, Direction::GoRight};
    auto string = move.toString();
    ASSERT_EQ(string, "Move startPosition: [0][1] direction: GoRight\n");
}

TEST(Move, toOstream) {
    Move move{sf::Vector2i{0, 1}, Direction::GoRight};
    std::stringstream ss;
    ss << move;
    auto string = ss.str();
    ASSERT_EQ(string, "Move startPosition: [0][1] direction: GoRight\n");
}