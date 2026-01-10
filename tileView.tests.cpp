#include "tileView.h"
#include <gmock/gmock.h>

using namespace ::testing;
using namespace SlidingTiles;

TEST(TileView, ObjectCreation) { TileView tileView{sf::Vector2i{1, 2}}; }
