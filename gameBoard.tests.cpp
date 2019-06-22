#include "gameBoard.h"
#include "move.h"
#include <gmock/gmock.h>

using namespace::testing;
using namespace SlidingTiles;

TEST(GameBoard, BoardSize) {
    ASSERT_EQ(4, GameBoard::boardSize);
}

TEST(GameBoard, loadGame) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    Tile t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[2][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 2,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][0];
    ASSERT_EQ(TileType::LeftBottom, t.getTileType()) << "Tile 3,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][1];
    ASSERT_EQ(TileType::Vertical, t.getTileType()) << "Tile 3,1 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][3];
    ASSERT_EQ(TileType::LeftTop, t.getTileType()) << "Tile 3,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][3];
    ASSERT_EQ(TileType::TopRight, t.getTileType()) << "Tile 0,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][2];
    ASSERT_EQ(TileType::BottomRight, t.getTileType()) << "Tile 0,2 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][1];
    ASSERT_EQ(TileType::EndRight, t.getTileType()) << "Tile 0,1 is of type " << tileTypeToString(t.getTileType());
}

TEST(GameBoard, saveAndLoadGame) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);

    std::vector<std::string> savedGame = gameBoard.serialiseGame();
    std::string emptyGame [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    gameBoard.loadGame(emptyGame);

    Tile t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    gameBoard.loadGame(savedGame);

    t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[2][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 2,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][0];
    ASSERT_EQ(TileType::LeftBottom, t.getTileType()) << "Tile 3,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][1];
    ASSERT_EQ(TileType::Vertical, t.getTileType()) << "Tile 3,1 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][3];
    ASSERT_EQ(TileType::LeftTop, t.getTileType()) << "Tile 3,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][3];
    ASSERT_EQ(TileType::TopRight, t.getTileType()) << "Tile 0,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][2];
    ASSERT_EQ(TileType::BottomRight, t.getTileType()) << "Tile 0,2 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][1];
    ASSERT_EQ(TileType::EndRight, t.getTileType()) << "Tile 0,1 is of type " << tileTypeToString(t.getTileType());
}

TEST(GameBoard, randomGame) {
    GameBoard gameBoard{};
    gameBoard.randomGame();
    int startTiles{0};
    int endTiles{0};
    int gameTiles{0};
    int emptyTiles{0};
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            TileType t = gameBoard.tiles[x][y].getTileType();
            if (isStartTileType(t)) {
                ++startTiles;
            } else if (isEndTileType(t)) {
                ++endTiles;
            } else if (isGameTileType(t)) {
                ++gameTiles;
            } else if (t == TileType::Empty) {
                ++emptyTiles;
            }
        }
    }
    ASSERT_EQ(startTiles, 1) << "A random game must have 1 start tile";
    ASSERT_EQ(endTiles, 1) << "A random game must have 1 end tile";
    ASSERT_GE(emptyTiles, 1) << "A random game must have at least 1 empty tile";
    ASSERT_GE(gameTiles, 1) << "A random game must have at least 1 game tile";
}

TEST(GameBoard, findNextTilePosition) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{1, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
    expectedPosition.x = 3;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
    expectedPosition.x = 2;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 2;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
    expectedPosition.x = 1;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
    expectedPosition.x = 0;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 2;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = 1;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
    expectedPosition.x = -2;
    expectedPosition.y = -2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 2;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

}

TEST(GameBoard, getOutputPosition2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"-", "-", "┤", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 0};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{1, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPosition3) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", "-", " ", " ",
        "├", " ", "┫", " ",
        " ", "-", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 2};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
    sf::Vector2i expectedPosition{-2, -2};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] of type: "
            << tileTypeToChar(gameBoard.tiles[tilePosition.x][tilePosition.y].getTileType()) << " getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPosition4) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"┬", "-", "-", "┐",
        "|", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{0, 1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPosition5) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"┌", "-", "-", "┐",
        "|", "┐", " ", "|",
        "┴", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 2};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{0, 1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPositionInvalid1) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{1, 0};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{-1, -1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPositionInvalid2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"|", "┘", " ", "-",
        "|", "├", "-", "┳",
        "┘", "-", " ", "|",
        " ", "|", "-", "|"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{3, 1};
    sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
    sf::Vector2i expectedPosition{-1, -1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = -2;
    expectedPosition.y = -2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, getOutputPositionOffTheBoard1) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"|┘┴└-├┳-┘- └┬|┐┌"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    {
        sf::Vector2i tilePosition{0, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{1, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{2, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::Unknown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 1};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 2};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{3, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{2, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{1, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{0, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{0, 2};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoDown});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{0, 1};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
}

TEST(GameBoard, getOutputPositionOffTheBoard2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"┤  ├  ┳     ┐   "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    {
        sf::Vector2i tilePosition{0, 0};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoLeft});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{0, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoRight});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
    {
        sf::Vector2i tilePosition{0, 3};
        sf::Vector2i nextTilePosition = gameBoard.getOutputPosition(Move{tilePosition, Direction::GoUp});
        sf::Vector2i expectedPosition{-1, -1};
        ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
    }
}

TEST(GameBoard, findAdjacentTilePosition) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├--┐┣┐ |┌┘ |└--┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    //std::cout << "First test unknown\n";
    sf::Vector2i nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::Unknown});
    sf::Vector2i expectedPosition{0, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Second test go right\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoRight});
    expectedPosition.x = 1;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go down...\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoDown});
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go left...\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoLeft});
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";


    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::Unknown});
    expectedPosition.x = 3;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoRight});
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoDown});
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoLeft});
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(Move{tilePosition, Direction::GoUp});
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, canSlideTile) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    Move move{sf::Vector2i{2, 0}, Direction::GoDown};
    ASSERT_TRUE(gameBoard.canSlideTile(move)) << "This slide should work\n";
}

TEST(GameBoard, canSlideTileOccupied) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    Move move{sf::Vector2i{2, 0}, Direction::GoRight};
    ASSERT_FALSE(gameBoard.canSlideTile(move)) << "This slide should not work because the tile is taken\n";
}

TEST(GameBoard, canSlideTileUnmoveables) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", " ", "┘",
        " ", " ", "-", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    Move moveStartTile{sf::Vector2i{1, 0}, Direction::GoLeft};
    ASSERT_FALSE(gameBoard.canSlideTile(moveStartTile)) << "This slide should not work because it is a start tile\n";

    Move moveEndTile{sf::Vector2i{1, 1}, Direction::GoRight};
    ASSERT_FALSE(gameBoard.canSlideTile(moveEndTile)) << "This slide should not work because it is an end tile\n";

    Move moveEmptyTile{sf::Vector2i{1, 2}, Direction::GoRight};
    ASSERT_FALSE(gameBoard.canSlideTile(moveEmptyTile)) << "This slide should not work because it is an empty tile\n";
}

TEST(GameBoard, canSlideTileOffTheBoard) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", " ", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    Move moveOffTop{sf::Vector2i{2, 0}, Direction::GoUp};
    ASSERT_FALSE(gameBoard.canSlideTile(moveOffTop)) << "This slide should not work because the new tile would move off the board\n";

    Move moveOffRight{sf::Vector2i{3, 0}, Direction::GoRight};
    ASSERT_FALSE(gameBoard.canSlideTile(moveOffRight)) << "This slide should not work because the new tile is off the right edge of the board\n";

    Move moveOffLeft{sf::Vector2i{0, 3}, Direction::GoLeft};
    ASSERT_FALSE(gameBoard.canSlideTile(moveOffLeft)) << "This slide should not work because the new tile is off the left side of the board\n";

    Move moveOffBottom{sf::Vector2i{0, 3}, Direction::GoDown};
    ASSERT_FALSE(gameBoard.canSlideTile(moveOffBottom)) << "This slide should not work because the new tile is off the bottom of the board\n";
}

TEST(GameBoard, isSolved) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", "-", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(6, result.size());
}

TEST(GameBoard, isSolved2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", "-", " ", " ",
        "├", "-", "┫", " ",
        " ", "-", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(3, result.size());
}

TEST(GameBoard, isNotSolved) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", " ", "┐",
        " ", "┣", "-", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"          - ┫--┤"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved3) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"          - ┤--┫"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved4) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"|┘ -|├-┳┘- | |-|"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, findStartTile) {
    GameBoard gameBoard{};
    gameBoard.loadGame("|┘ -|├-┳┘- | |-|");
    auto startTile = gameBoard.findStartTile();
    auto startTilePos = startTile->getTilePosition();
    ASSERT_THAT(1, startTilePos.x);
    ASSERT_THAT(1, startTilePos.y);
}

TEST(GameBoard, findStartTileMissing) {
    GameBoard gameBoard{};
    gameBoard.loadGame("                ");
    auto startTile = gameBoard.findStartTile();
    ASSERT_EQ(startTile, nullptr);
}

TEST(GameBoard, serialiseGameToString) {
    GameBoard gameBoard{};
    std::string game = "|┘ -|├-┳┘- | |-|";
    gameBoard.loadGame(game);
    std::string serialisedGame = gameBoard.serialiseGameToString();
    ASSERT_EQ(game, serialisedGame);
}

TEST(GameBoard, printGame) {
    //Based on http://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest
    GameBoard gameBoard{};
    std::string game = "|┘ -|├-┳┘- | |-|";
    gameBoard.loadGame(game);

    // This can be an ofstream as well or any other ostream
    std::stringstream buffer;
    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();
    // Redirect cout to our stringstream buffer or any other ostream
    std::cout.rdbuf(buffer.rdbuf());
    // Use cout as usual
    gameBoard.printGame();
    // When done redirect cout to its old self
    std::cout.rdbuf(sbuf);

    std::string output = buffer.str();
    ASSERT_EQ(game + '\n', output);
}

TEST(GameBoard, DISABLED_setWinnerTiles) {
    GameBoard gameBoard{};
    std::string game = "|┘ -|├-┳┘- | |-|";
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> fakeSolutionPath{};
    fakeSolutionPath.push_back(sf::Vector2i{0, 1});
    fakeSolutionPath.push_back(sf::Vector2i{0, 2});
    fakeSolutionPath.push_back(sf::Vector2i{1, 2});
    fakeSolutionPath.push_back(sf::Vector2i{1, 3});
    auto on = 0, off = 0;
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            if (gameBoard.tiles[x][y].isWinner()) {
                ++on;
            } else {
                ++off;
            }
        }
    }
    ASSERT_THAT(on, 4);
    ASSERT_THAT(GameBoard::boardSize * GameBoard::boardSize - 4, off);
}

TEST(GameBoard, DISABLED_clearWinnerTiles) {
    GameBoard gameBoard{};
    std::string game = "|┘ -|├-┳┘- | |-|";
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> fakeSolutionPath{};
    fakeSolutionPath.push_back(sf::Vector2i{0, 1});
    fakeSolutionPath.push_back(sf::Vector2i{0, 2});
    fakeSolutionPath.push_back(sf::Vector2i{1, 2});
    fakeSolutionPath.push_back(sf::Vector2i{1, 3});
    auto on = 0, off = 0;
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            if (gameBoard.tiles[x][y].isWinner()) {
                ++on;
            } else {
                ++off;
            }
        }
    }
    ASSERT_THAT(on, 4);
    ASSERT_THAT(GameBoard::boardSize * GameBoard::boardSize - 4, off);

    on = 0;
    off = 0;
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            if (gameBoard.tiles[x][y].isWinner()) {
                ++on;
            } else {
                ++off;
            }
        }
    }
    ASSERT_THAT(on, 0);
    ASSERT_THAT(GameBoard::boardSize * GameBoard::boardSize, off);
}

