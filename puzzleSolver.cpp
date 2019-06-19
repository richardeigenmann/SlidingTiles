#include "puzzleSolver.h"
#include <cassert>
#include <queue>

const int SlidingTiles::PuzzleSolver::DEFAULT_DEPTH;

std::experimental::optional<SlidingTiles::MoveNode> SlidingTiles::PuzzleSolver::possibleMoves(MoveNode & moveNode) {
    assert((moveNode.startPosition.x >= -1) && (moveNode.startPosition.x <= GameBoard::boardSize)); // NOLINT (hicpp-no-array-decay)
    assert((moveNode.startPosition.y >= -1) && (moveNode.startPosition.y <= GameBoard::boardSize)); // NOLINT (hicpp-no-array-decay)

    GameBoard gameBoard{};
    gameBoard.loadGame(moveNode.endingBoard);
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            sf::Vector2i position{x, y};
            if (gameBoard.getTile(x,y).isMoveable) {
                if (moveNode.direction != Direction::GoDown && gameBoard.canSlideTile(Move{position, Direction::GoUp})) {
                    MoveNode childNode{position, Direction::GoUp};
                    childNode.setParent(moveNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(moveNode.endingBoard); // restore
                }
                if (moveNode.direction != Direction::GoUp && gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    MoveNode childNode{position, Direction::GoDown};
                    childNode.setParent(moveNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(moveNode.endingBoard); // restore
                }
                if (moveNode.direction != Direction::GoRight && gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    MoveNode childNode{position, Direction::GoLeft};
                    childNode.setParent(moveNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(moveNode.endingBoard); // restore
                }
                if (moveNode.direction != Direction::GoLeft && gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    MoveNode childNode{position, Direction::GoRight};
                    childNode.setParent(moveNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(moveNode.endingBoard); // restore
                }
            }
        }
    }
    return {};
}

std::experimental::optional<SlidingTiles::MoveNode> SlidingTiles::PuzzleSolver::addPossibleMoves(MoveNode &moveNode, const int levels) {
    assert(moveNode.startPosition.x >= -1 && moveNode.startPosition.x <= GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
    assert(moveNode.startPosition.y >= -1 && moveNode.startPosition.y <= GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << moveNode.toString();

    auto opt = possibleMoves(moveNode);
    if (opt) {
        return opt;
    }
    //std::cout << "Entering if with levels: " << levels << "\n";
    for (MoveNode & mn : moveNode.possibleMoves) {
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
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    //moveNode.possibleMoves.insert(std::end(moveNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
}

std::experimental::optional<SlidingTiles::MoveNode> SlidingTiles::PuzzleSolver::buildTree(GameBoard & gameBoard, int depth) {
    gameBoard.rootNode.possibleMoves.clear();
    gameBoard.rootNode.endingBoard = gameBoard.serialiseGame();
    return addPossibleMoves(gameBoard.rootNode, depth);
}

void SlidingTiles::PuzzleSolver::saveSolution(GameBoard & gameBoard) {
    assert(gameBoard.rootNode.startPosition.x >= -1 && gameBoard.rootNode.startPosition.x <= GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
    assert(gameBoard.rootNode.startPosition.y >= -1 && gameBoard.rootNode.startPosition.y <= GameBoard::boardSize); // NOLINT (hicpp-no-array-decay)
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(gameBoard.rootNode);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if ( ! gameBoard.isSolved().empty()) {
            while (t.parent != nullptr) {
                auto iteratorFront = gameBoard.solution.begin();
                gameBoard.solution.insert(iteratorFront, t);
                t = *t.parent;
            }
            return;
        };
        for (const auto & possibleMove : t.possibleMoves) {
            Q.push(possibleMove);
        }
    }
    gameBoard.solution.clear();
}

SlidingTiles::GameBoard SlidingTiles::PuzzleSolver::generateRandomGame(std::size_t emptyTiles, std::size_t maxDepth) {
    SlidingTiles::PuzzleSolver puzzleSolver;
    while (true) {
        GameBoard gameBoard{};
        gameBoard.randomGame(emptyTiles);
        auto solution = buildTree(gameBoard, maxDepth);
        //saveSolution(gameBoard);
        if (solution) {
            std::cout << "\n{\n\t\"SerializedGame\": \""
            << gameBoard.serialiseGameToString()
            << '\"'
            << ",\n"
            << solution.value().enumerateMoves() << "\n"
            << "},\n";
            return gameBoard;
        }
        std::cout << "Discarding game as it can't be solved in " << maxDepth << " moves\n";
    }
}

void SlidingTiles::PuzzleSolver::generateGame(std::size_t emptyTiles, std::size_t maxDepth) {
    GameBoard gameBoard = generateRandomGame(emptyTiles, maxDepth);
}

void SlidingTiles::PuzzleSolver::generateGames(std::size_t games) {
    while (games > 0) {
        //std::size_t emptyTiles = (rand() % MAXIMUM_EMPTY_TILES) + 1;
        std::size_t emptyTiles = ud(randomNumberGenerator);
        generateGame(emptyTiles, DEFAULT_DEPTH);
        --games;
    }
}
