#include "puzzleSolver.h"
#include "move.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(PuzzleSolver, possibleMovesNone) {
  std::wstring game{L"├┫              "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.buildTree(gameBoard, 2);
  ASSERT_THAT(gameBoard.rootNode.possibleMoves.size(), 0);
}

TEST(PuzzleSolver, possibleMovesOne) {
  std::wstring game{L"├-┫             "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::MoveNode rootNode{sf::Vector2i{-1, -1},
                                  SlidingTiles::Direction::Unknown};
  rootNode.endingBoard = gameBoard.serialiseGameToWstring();
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.possibleMoves(rootNode);
  ASSERT_THAT(rootNode.possibleMoves.size(), 1);
  SlidingTiles::MoveNode move = rootNode.possibleMoves[0];
  sf::Vector2i expectedTile{1, 0};
  ASSERT_EQ(move.startPosition, expectedTile)
      << "Expect tile [1][0] to be a possible move but returned tile is ["
      << move.startPosition.x << "][" << move.startPosition.y << "] \n";
  int up{0};
  int down{0};
  int left{0};
  int right{0};
  for (const auto &moveNode : rootNode.possibleMoves) {
    if (moveNode.direction == SlidingTiles::Direction::GoDown) {
      ++down;
    } else if (moveNode.direction == SlidingTiles::Direction::GoUp) {
      ++up;
    } else if (moveNode.direction == SlidingTiles::Direction::GoLeft) {
      ++left;
    } else if (moveNode.direction == SlidingTiles::Direction::GoRight) {
      ++right;
    }
  }
  ASSERT_EQ(up, 0);
  ASSERT_EQ(down, 1);
  ASSERT_EQ(left, 0);
  ASSERT_EQ(right, 0);
}

TEST(PuzzleSolver, possibleMovesDontGoBack) {
  std::wstring game{L"├ ┫  -          "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::MoveNode rootNode{sf::Vector2i{1, 1},
                                  SlidingTiles::Direction::GoDown};
  rootNode.endingBoard = gameBoard.serialiseGameToWstring();
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.possibleMoves(rootNode);
  ASSERT_THAT(rootNode.possibleMoves.size(), 3);
  int up{0};
  int down{0};
  int left{0};
  int right{0};
  for (const auto &moveNode : rootNode.possibleMoves) {
    if (moveNode.direction == SlidingTiles::Direction::GoDown) {
      ++down;
    } else if (moveNode.direction == SlidingTiles::Direction::GoUp) {
      ++up;
    } else if (moveNode.direction == SlidingTiles::Direction::GoLeft) {
      ++left;
    } else if (moveNode.direction == SlidingTiles::Direction::GoRight) {
      ++right;
    }
  }
  ASSERT_EQ(up, 0);
  ASSERT_EQ(down, 1);
  ASSERT_EQ(left, 1);
  ASSERT_EQ(right, 1);
}

TEST(PuzzleSolver, addPossibleMoves) {
  // builds on possibleMovesOne
  std::wstring game{L"├-┫             "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.buildTree(gameBoard, 3);
  ASSERT_THAT(gameBoard.rootNode.possibleMoves.size(), 1);

  SlidingTiles::MoveNode onlyChild = gameBoard.rootNode.possibleMoves[0];
  ASSERT_THAT(onlyChild.possibleMoves.size(), 3);
  int up{0};
  int down{0};
  int left{0};
  int right{0};
  for (const auto &node : onlyChild.possibleMoves) {
    if (node.direction == SlidingTiles::Direction::GoDown) {
      ++down;
    } else if (node.direction == SlidingTiles::Direction::GoUp) {
      ++up;
    } else if (node.direction == SlidingTiles::Direction::GoLeft) {
      ++left;
    } else if (node.direction == SlidingTiles::Direction::GoRight) {
      ++right;
    }
  }
  ASSERT_EQ(up, 0);
  ASSERT_EQ(down, 1);
  ASSERT_EQ(left, 1);
  ASSERT_EQ(right, 1);
}

TEST(PuzzleSolver, addPossibleMoves3Deep) {
  // builds on addPossibleMoves which builds on possibleMovesOne
  std::wstring game{L"├-┫             "};
  SlidingTiles::PuzzleSolver puzzleSolver;
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  puzzleSolver.buildTree(gameBoard, 3);
  ASSERT_THAT(gameBoard.rootNode.possibleMoves.size(), 1);

  SlidingTiles::MoveNode onlyChild = gameBoard.rootNode.possibleMoves[0];
  ASSERT_THAT(onlyChild.possibleMoves.size(), 3);
  int up{0};
  int down{0};
  SlidingTiles::MoveNode downNode{sf::Vector2i{-1, -1},
                                  SlidingTiles::Direction::Unknown};
  int left{0};
  SlidingTiles::MoveNode leftNode{sf::Vector2i{-1, -1},
                                  SlidingTiles::Direction::Unknown};
  int right{0};
  SlidingTiles::MoveNode rightNode{sf::Vector2i{-1, -1},
                                   SlidingTiles::Direction::Unknown};
  for (const auto &node : onlyChild.possibleMoves) {
    if (node.direction == SlidingTiles::Direction::GoDown) {
      ++down;
      ASSERT_EQ(node.possibleMoves.size(), 3);
      downNode = std::move(node);
    } else if (node.direction == SlidingTiles::Direction::GoUp) {
      ++up;
    } else if (node.direction == SlidingTiles::Direction::GoLeft) {
      ++left;
      ASSERT_EQ(node.possibleMoves.size(), 1);
      leftNode = std::move(node);
    } else if (node.direction == SlidingTiles::Direction::GoRight) {
      ++right;
      ASSERT_EQ(node.possibleMoves.size(), 2);
      rightNode = std::move(node);
    }
  }
  ASSERT_EQ(up, 0);
  ASSERT_EQ(down, 1);
  ASSERT_EQ(left, 1);
  ASSERT_EQ(right, 1);

  // Second Level:
  int up2{0};
  int down2{0};
  int left2{0};
  int right2{0};
  for (const auto &node : downNode.possibleMoves) {
    if (node.direction == SlidingTiles::Direction::GoDown) {
      ++down2;
      ASSERT_EQ(node.possibleMoves.size(), 2);
    } else if (node.direction == SlidingTiles::Direction::GoUp) {
      ++up2;
    } else if (node.direction == SlidingTiles::Direction::GoLeft) {
      ++left2;
      ASSERT_EQ(node.possibleMoves.size(), 2);
    } else if (node.direction == SlidingTiles::Direction::GoRight) {

      ++right2;
      ASSERT_EQ(node.possibleMoves.size(), 3);
    }
  }
  ASSERT_EQ(up2, 0);
  ASSERT_EQ(down2, 1);
  ASSERT_EQ(left2, 1);
  ASSERT_EQ(right2, 1);
}

TEST(PuzzleSolver, isSolvedIn1Move) {
  std::wstring game{L"├ ┫  -          "};
  SlidingTiles::PuzzleSolver puzzleSolver;
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  puzzleSolver.buildTree(gameBoard, 3);
  puzzleSolver.saveSolution(gameBoard);
  ASSERT_THAT(gameBoard.solution.size(), 1)
      << "There should be at least one solution for this puzzle";
}

TEST(PuzzleSolver, isSolvedIn2Moves) {
  std::wstring game{L"├ ┫      -      "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.buildTree(gameBoard, 3);
  puzzleSolver.saveSolution(gameBoard);
  ASSERT_THAT(gameBoard.solution.size(), 2)
      << "There should be at least one solution for this puzzle";
}

TEST(PuzzleSolver, noSolution) {
  std::wstring game{L"├ ┫  |          "};
  SlidingTiles::GameBoard gameBoard{};
  gameBoard.loadGame(game);
  SlidingTiles::PuzzleSolver puzzleSolver;
  puzzleSolver.buildTree(gameBoard, 3);
  puzzleSolver.saveSolution(gameBoard);
  ASSERT_THAT(gameBoard.solution.size(), 0)
      << "There should be no solution for this puzzle";
}
