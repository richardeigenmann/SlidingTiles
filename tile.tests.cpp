#include "tile.h"
#include <gmock/gmock.h>
#include "gameBoard.h"

TEST(Tile, ObjectCreation) {
    SlidingTiles::Tile tile;
}

TEST(Tile, outputDirectionStartRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::StartRight);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);
}

TEST(Tile, outputDirectionStartLeft) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::StartLeft);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);
}

TEST(Tile, outputDirectionStartTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::StartTop);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);
}

TEST(Tile, outputDirectionStartBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::StartBottom);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);
}

TEST(Tile, outputDirectionEndRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::EndRight);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndLeft) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::EndLeft);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::EndTop);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::EndBottom);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionVertical) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::Vertical);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionHorizontal) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::Horizontal);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);
}

TEST(Tile, outputDirectionBottomRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::BottomRight);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);
}

TEST(Tile, outputDirectionLeftTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::LeftTop);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionLeftBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::LeftBottom);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);
}

TEST(Tile, TopRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(SlidingTiles::TileType::TopRight);
    SlidingTiles::Direction newDirection = tile.outputDirection(SlidingTiles::Direction::Unknown);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoDown);
    ASSERT_THAT(SlidingTiles::Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoUp);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoRight);
    ASSERT_THAT(SlidingTiles::Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(SlidingTiles::Direction::GoLeft);
    ASSERT_THAT(SlidingTiles::Direction::GoUp, newDirection);
}

TEST(Tile, setTileTypeChar) {
    SlidingTiles::Tile tile;

    tile.setTileType("-");
    ASSERT_EQ(SlidingTiles::TileType::Horizontal, tile.getTileType());

    tile.setTileType("|");
    ASSERT_EQ(SlidingTiles::TileType::Vertical, tile.getTileType());


    tile.setTileType("┐");
    ASSERT_EQ(SlidingTiles::TileType::LeftBottom, tile.getTileType());

    tile.setTileType("└");
    ASSERT_EQ(SlidingTiles::TileType::TopRight, tile.getTileType());

    tile.setTileType("┘");
    ASSERT_EQ(SlidingTiles::TileType::LeftTop, tile.getTileType());

    tile.setTileType("┌");
    ASSERT_EQ(SlidingTiles::TileType::BottomRight, tile.getTileType());


    tile.setTileType("├");
    ASSERT_EQ(SlidingTiles::TileType::StartRight, tile.getTileType());

    tile.setTileType("┤");
    ASSERT_EQ(SlidingTiles::TileType::StartLeft, tile.getTileType());

    tile.setTileType("┬");
    ASSERT_EQ(SlidingTiles::TileType::StartBottom, tile.getTileType());

    tile.setTileType("┴");
    ASSERT_EQ(SlidingTiles::TileType::StartTop, tile.getTileType());


    tile.setTileType("┣");
    ASSERT_EQ(SlidingTiles::TileType::EndRight, tile.getTileType());

    tile.setTileType("┫");
    ASSERT_EQ(SlidingTiles::TileType::EndLeft, tile.getTileType());

    tile.setTileType("┳");
    ASSERT_EQ(SlidingTiles::TileType::EndBottom, tile.getTileType());

    tile.setTileType("┻");
    ASSERT_EQ(SlidingTiles::TileType::EndTop, tile.getTileType());


    tile.setTileType(" ");
    ASSERT_EQ(SlidingTiles::TileType::Empty, tile.getTileType());
}

TEST(Tile, transition) {
    std::string game [SlidingTiles::GameBoard::boardSize][SlidingTiles::GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    SlidingTiles::GameBoard gameBoard;
    gameBoard.loadGame(game);
    SlidingTiles::Tile t = gameBoard.tiles[0][0];
    sf::Vector2i newPosition{1, 0};
    t.transition(newPosition);
    //bool result = t.transition(topLeftPostion);
    //ASSERT_TRUE(result) << "Transitioning should be possible first time\n";
    //result = t.transition(topLeftPostion);
    //ASSERT_FALSE(result) << "Transitioning should not be possible when transitioning in progress\n";
    ASSERT_EQ(t.getTilePosition().x, 1 );
    ASSERT_EQ(t.getTilePosition().y, 0 );
}
