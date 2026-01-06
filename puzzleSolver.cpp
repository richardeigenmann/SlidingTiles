#include "direction.h"
#include "move.h"
#include "moveNode.h"
#include "puzzleSolver.h"
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

const int SlidingTiles::PuzzleSolver::DEFAULT_DEPTH;

auto SlidingTiles::PuzzleSolver::possibleMoves(MoveNode &moveNode)
    -> std::optional<SlidingTiles::MoveNode> {
  assert((moveNode.startPosition.x >= -1) &&
         (moveNode.startPosition.x <= GameBoard::boardSize)); // NOLINT (hicpp-no-array-decay)
  assert((moveNode.startPosition.y >= -1) &&
         (moveNode.startPosition.y <= GameBoard::boardSize)); // NOLINT (hicpp-no-array-decay)

  // Define all possible directions and their "opposites" to prevent backtracking
  const std::vector<std::pair<Direction, Direction>> directions = {
    {Direction::GoUp,    Direction::GoDown},
    {Direction::GoDown,  Direction::GoUp},
    {Direction::GoLeft,  Direction::GoRight},
    {Direction::GoRight, Direction::GoLeft}
  };

  GameBoard gameBoard{};
  gameBoard.loadGameNoGui(moveNode.endingBoard);
  for (int x = 0; x < GameBoard::boardSize; ++x) {
    for (int y = 0; y < GameBoard::boardSize; ++y) {
      if (!gameBoard.getTile(x, y)->isMoveable) { continue; }

      const sf::Vector2i position{x, y};

      for (const auto& [dir, opposite] : directions) {
        // Skip if this move just undoes the previous move
        if (moveNode.direction == opposite) { continue; }

        const Move move{position, dir};
        if (gameBoard.canSlideTile(move)) {
          MoveNode childNode{position, dir};
          childNode.setParent(moveNode);

          gameBoard.moveTileNoGui(childNode);
          childNode.setEndingBoard(gameBoard.serialiseGameToWstring());
          moveNode.possibleMoves.push_back(childNode);

          if (!gameBoard.isSolved().empty()) {
            return childNode;
          }

          // Restore board state for the next direction/tile check
          gameBoard.loadGameNoGui(moveNode.endingBoard);
        }
      }
    }
  }
  return {};
}

auto SlidingTiles::PuzzleSolver::addPossibleMoves(MoveNode &moveNode,
                                                  const int levels)
    -> std::optional<SlidingTiles::MoveNode> {
  assert(moveNode.startPosition.x >= -1 &&
         moveNode.startPosition.x <=
             GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
  assert(moveNode.startPosition.y >= -1 &&
         moveNode.startPosition.y <= GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)

  auto opt = possibleMoves(moveNode);
  if (opt) {
    return opt;
  }
  for (MoveNode &mn : moveNode.possibleMoves) {
    // note the & above to ensure we work with the members and not a copy
    mn.depth = moveNode.depth + 1;
    if (levels > 0) {
      opt = addPossibleMoves(mn, levels - 1);
      if (opt) {
        return opt;
      }
    }
  }
  return {};
  // note do the insert after the recursive call above because insert copies the
  // object and it might copy without the content in the vector!
  // moveNode.possibleMoves.insert(std::end(moveNode.possibleMoves),
  // std::begin(possMoves), std::end(possMoves));
}

auto SlidingTiles::PuzzleSolver::buildTree(GameBoard &gameBoard, int depth)
    -> std::optional<SlidingTiles::MoveNode> {
  gameBoard.rootNode.possibleMoves.clear();
  gameBoard.rootNode.endingBoard = gameBoard.serialiseGameToWstring();
  return addPossibleMoves(gameBoard.rootNode, depth);
}

void SlidingTiles::PuzzleSolver::saveSolution(GameBoard &gameBoard) {
  assert(gameBoard.rootNode.startPosition.x >= -1 &&
         gameBoard.rootNode.startPosition.x <=
             GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
  assert(gameBoard.rootNode.startPosition.y >= -1 &&
         gameBoard.rootNode.startPosition.y <=
             GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
  // inspired by https://gist.github.com/douglas-vaz/5072998
  std::queue<MoveNode> Q;
  Q.push(gameBoard.rootNode);
  while (!Q.empty()) {
    MoveNode t = Q.front();
    Q.pop();
    gameBoard.loadGameNoGui(t.endingBoard);
    if (!gameBoard.isSolved().empty()) {
      while (t.parent != nullptr) {
        auto iteratorFront = gameBoard.solution.begin();
        gameBoard.solution.insert(iteratorFront, t);
        t = *t.parent;
      }
      return;
    }
    for (const auto &possibleMove : t.possibleMoves) {
      Q.push(possibleMove);
    }
  }
  gameBoard.solution.clear();
}

auto SlidingTiles::PuzzleSolver::generateRandomGameBoardAndSolution(
    std::size_t emptyTiles, std::size_t maxDepth)
    -> std::tuple<SlidingTiles::GameBoard, std::optional<SlidingTiles::MoveNode>> {
  while (true) {
    GameBoard gameBoard{};
    gameBoard.randomGame(emptyTiles);
    auto solution = buildTree(gameBoard, maxDepth);

    if (solution) {
      return std::tuple(gameBoard, solution);
    }
    std::cout << "Discarding game as it can't be solved in " << maxDepth
              << " moves\n";
  }
}

auto SlidingTiles::PuzzleSolver::generateRandomGame(std::size_t emptyTiles,
                                                    std::size_t maxDepth)
    -> SlidingTiles::GameBoard {
  auto [gameBoard, solution] =
      generateRandomGameBoardAndSolution(emptyTiles, maxDepth);
  std::wcout << L"\n{\n\t\"SerializedGame\": \""
    << gameBoard.serialiseGameToWstring()
    << L"\"\n"
    << L"},\n";
  return gameBoard;
}

void SlidingTiles::PuzzleSolver::generateGames(std::size_t games) {
  while (games > 0) {
    const std::size_t emptyTiles = ud(randomNumberGenerator);
    generateRandomGame(emptyTiles, DEFAULT_DEPTH);
    --games;
  }
}
