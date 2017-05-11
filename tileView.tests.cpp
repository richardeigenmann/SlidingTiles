#include "tileView.h"
#include <gmock/gmock.h>

using namespace ::testing;
using namespace SlidingTiles;

TEST(TileView, ObjectCreation) {
    TileView tileView {sf::Vector2i {1,2}};
}

TEST(TileView, DISABLED_transition) {
    TileView tileView {sf::Vector2i {1,2}};
    //tileView.transition(sf::Vector2i{0, 0});
    //ASSERT_EQ(tileView.transitioning, true);
}
