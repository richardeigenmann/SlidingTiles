#include "direction.h"
#include "gameBoard.h"
#include "gameSettings.h"
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

auto SlidingTiles::PuzzleSolver::checkTileDirections(MoveNode &moveNode, GameBoard &gameBoard, sf::Vector2i position)
  -> std::optional<SlidingTiles::MoveNode>  {

  static const std::vector<std::pair<Direction, Direction>> directions = {
    {Direction::GoUp,    Direction::GoDown},
    {Direction::GoDown,  Direction::GoUp},
    {Direction::GoLeft,  Direction::GoRight},
    {Direction::GoRight, Direction::GoLeft}
  };

  for (const auto& [dir, opposite] : directions) {
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

      // Restore board state for the next direction check
      gameBoard.loadGameNoGui(moveNode.endingBoard);
    }
  }
  return std::nullopt;
}

auto SlidingTiles::PuzzleSolver::possibleMoves(MoveNode &moveNode)
    -> std::optional<SlidingTiles::MoveNode> {

    GameBoard gameBoard{};
    gameBoard.loadGameNoGui(moveNode.endingBoard);

    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            // Level 1: Find a movable tile
            if (!gameBoard.getTile(x, y)->isMoveable) { continue; }

            // Level 2: Check all 4 directions for this specific tile
            auto winningNode = checkTileDirections(moveNode, gameBoard, {x, y});
            if (winningNode) { return winningNode; }
        }
    }
    return std::nullopt;
}

auto SlidingTiles::PuzzleSolver::addPossibleMoves(MoveNode &moveNode, const size_t levels) // NOLINT(misc-no-recursion)
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
      opt = addPossibleMoves(mn, levels - 1); // NOLINT(misc-no-recursion)
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

auto SlidingTiles::PuzzleSolver::buildTree(GameBoard &gameBoard, size_t depth)
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

auto SlidingTiles::PuzzleSolver::generateRandomGameBoardAndSolution(GameSettings settings)
    -> std::tuple<SlidingTiles::GameBoard, std::optional<SlidingTiles::MoveNode>> {
  while (true) {
    GameBoard gameBoard{};
    gameBoard.randomGame(settings.emptyTiles);
    auto solution = buildTree(gameBoard, settings.maxDepth);

    if (solution) {
      return {gameBoard, solution};
    }
    std::cout << "Discarding game as it can't be solved in " << settings.maxDepth
              << " moves\n";
  }
}

auto SlidingTiles::PuzzleSolver::generateRandomGame(GameSettings settings)
    -> SlidingTiles::GameBoard {
  auto [gameBoard, solution] =
      generateRandomGameBoardAndSolution(settings);
  std::wcout << L"\n{\n\t\"SerializedGame\": \""
    << gameBoard.serialiseGameToWstring()
    << L"\"\n"
    << L"},\n";
  return gameBoard;
}

void SlidingTiles::PuzzleSolver::generateGames(std::size_t games) {
  while (games > 0) {
    const std::size_t emptyTiles = ud(randomNumberGenerator);
    generateRandomGame(GameSettings{.emptyTiles = emptyTiles, .maxDepth = DEFAULT_DEPTH});
    --games;
  }
}
