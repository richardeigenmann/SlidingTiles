#include "puzzleSolver.h"
#include <queue>
#include <assert.h> // assert

using namespace SlidingTiles;

const int PuzzleSolver::DEFAULT_DEPTH;

std::experimental::optional<MoveNode> PuzzleSolver::possibleMoves(MoveNode & parentNode) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);

    GameBoard gameBoard{};
    gameBoard.loadGame(parentNode.endingBoard);
    for (int x = 0; x < GameBoard::boardSize; ++x)
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            sf::Vector2i position{x, y};
            if (gameBoard.tiles[x][y].isMoveable) {
                if (parentNode.direction != Direction::GoDown && gameBoard.canSlideTile(Move{position, Direction::GoUp})) {
                    MoveNode childNode{position, Direction::GoUp};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    parentNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoUp && gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    MoveNode childNode{position, Direction::GoDown};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    parentNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoRight && gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    MoveNode childNode{position, Direction::GoLeft};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    parentNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoLeft && gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    MoveNode childNode{position, Direction::GoRight};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    parentNode.possibleMoves.push_back(childNode);
                    if ( ! gameBoard.isSolved().empty() ) {
                        return childNode;
                    }
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
            }
        }
        return {};
}

std::experimental::optional<MoveNode> PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int levels) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    auto opt = possibleMoves(parentNode);
    if (opt) {
        return opt;
    }
    //std::cout << "Entering if with levels: " << levels << "\n";
    for (MoveNode & mn : parentNode.possibleMoves) {
        // note the & above to ensure we work with the members and not a copy
        mn.depth = parentNode.depth + 1;
        if (levels > 0) {
            opt = addPossibleMoves(mn, levels - 1);
            if (opt) {
                return opt;
            }
        }
    }
    return {};
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    //parentNode.possibleMoves.insert(std::end(parentNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
}

std::experimental::optional<MoveNode> PuzzleSolver::buildTree(GameBoard & gameBoard, int depth) {
    gameBoard.rootNode.possibleMoves.clear();
    gameBoard.rootNode.endingBoard = gameBoard.serialiseGame();
    return addPossibleMoves(gameBoard.rootNode, depth);
}

void PuzzleSolver::saveSolution(GameBoard & gameBoard) {
    assert(gameBoard.rootNode.startPosition.x >= -1 && gameBoard.rootNode.startPosition.x <= GameBoard::boardSize);
    assert(gameBoard.rootNode.startPosition.y >= -1 && gameBoard.rootNode.startPosition.y <= GameBoard::boardSize);
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
        for (std::size_t i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    gameBoard.solution.clear();
    return;
}

GameBoard PuzzleSolver::generateRandomGame(std::size_t emptyTiles, std::size_t maxDepth) {
    PuzzleSolver puzzleSolver;
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

            //if (gameBoard.solution.size() > 0) {
                return gameBoard;
            //}

        }
        std::cout << "Discarding game as it can't be solved in " << maxDepth << " moves\n";
        
    }
}

void PuzzleSolver::generateGame(std::size_t emptyTiles, std::size_t maxDepth) {
    GameBoard gameBoard = generateRandomGame(emptyTiles, maxDepth);

}

void PuzzleSolver::generateGames(std::size_t games) {
    while (games > 0) {
        std::size_t emptyTiles = (rand() % 13) + 1;
        generateGame(emptyTiles, DEFAULT_DEPTH);
        --games;
    }
}
