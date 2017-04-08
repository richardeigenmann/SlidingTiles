#include "button.h"
#include <gmock/gmock.h>

using namespace ::testing;
using namespace SlidingTiles;

TEST(ButtonTest, Constructor) {
    Button button {"assets/button_next.png"};
    ASSERT_THAT(1, Eq(1));
}

TEST(ButtonTest, ConstructorBadFilename) {
    Button button {"assets/no_such_file.png"};
    ASSERT_THAT(1, Eq(1));
}

TEST(ButtonTest, setPosition) {
    Button button {"assets/button_next.png"};
    button.setPosition(10.1, 20.2);
    ASSERT_EQ(10.1f, button.getSprite().getPosition().x);
    ASSERT_EQ(20.2f, button.getSprite().getPosition().y);
}

TEST(ButtonTest, render) {
    Button button {"assets/button_next.png"};
    button.render();
}

TEST(ButtonTest, mouseReleased) {
    Button button {"assets/button_next.png"};
    button.setPosition(10.1, 20.2);
    bool inside = button.mouseReleased( sf::Vector2i{ 11,22 });
    bool outside = button.mouseReleased( sf::Vector2i{ 8,2 });
    ASSERT_TRUE(inside);
    ASSERT_FALSE(outside);
}
