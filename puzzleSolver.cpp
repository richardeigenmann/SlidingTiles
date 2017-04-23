#include "puzzleSolver.h"
#include <queue>
#include <assert.h> // assert

using namespace SlidingTiles;

const int PuzzleSolver::DEFAULT_DEPTH;

std::vector<MoveNode> PuzzleSolver::possibleMoves(const MoveNode & parentNode) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);

    MoveNode moveNode{sf::Vector2i{-1, -1}, Direction::Unknown};
    moveNode.endingBoard = parentNode.endingBoard;
    moveNode.setParent(parentNode);
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
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoUp && gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    MoveNode childNode{position, Direction::GoDown};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoRight && gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    MoveNode childNode{position, Direction::GoLeft};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoLeft && gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    MoveNode childNode{position, Direction::GoRight};
                    childNode.setParent(parentNode);
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
            }
        }
    return moveNode.possibleMoves;
}

void PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int levels) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    std::vector<MoveNode> possMoves = possibleMoves(parentNode);
    //std::cout << "Entering if with levels: " << levels << "\n";
    for (MoveNode & mn : possMoves) {
        // note the & above to ensure we work with the members and not a copy
        mn.depth = parentNode.depth + 1;
        if (levels > 0) {
            addPossibleMoves(mn, levels - 1);
        }
    }
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    parentNode.possibleMoves.insert(std::end(parentNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
}

/*MoveNode PuzzleSolver::getTree(const std::vector<std::string> & game, int depth) {
    MoveNode rootNode{};
    rootNode.endingBoard = game;
    addPossibleMoves(rootNode, depth);
    return rootNode;
}

MoveNode PuzzleSolver::getTree(const std::wstring & game, int depth) {
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    return getTree(gameBoard.serialiseGame(), depth);
}*/

void PuzzleSolver::buildTree(GameBoard & gameBoard, int depth) {
    gameBoard.rootNode.possibleMoves.clear();
    gameBoard.rootNode.endingBoard = gameBoard.serialiseGame();
    addPossibleMoves(gameBoard.rootNode, depth);
}

int PuzzleSolver::hasASolution(const MoveNode & node) {
    assert(node.startPosition.x >= -1 && node.startPosition.x <= GameBoard::boardSize);
    assert(node.startPosition.y >= -1 && node.startPosition.y <= GameBoard::boardSize);
    // inspired by https://gist.github.com/douglas-vaz/5072998
    GameBoard gameBoard;
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if (gameBoard.isSolved().size() > 0) {
            return t.depth;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    return -1;
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
        if (gameBoard.isSolved().size() > 0) {
            //std::cout << "RootNode: " << gameBoard.rootNode.toString();
            std::cout << "Solution: " << t.toString();
            if (t.parent == nullptr) {
                std::cout << "First Yes, nullptr\n";
            } else {
                std::cout << "First Not nullptr\n";

            }
            //while (t.parent != nullptr) {
            {
                auto iteratorFront = gameBoard.solution.begin();
                gameBoard.solution.insert(iteratorFront, t);
                std::cout << "Inserting #" << t.id << "\n";
            }
            t = *t.parent;
            if (t.parent == nullptr) {
             std::cout << "Second Yes, nullptr\n";
            } else {
             std::cout << "Second Not nullptr\n";        
            }
            {
                auto iteratorFront = gameBoard.solution.begin();
                gameBoard.solution.insert(iteratorFront, t);
                std::cout << "Inserting #" << t.id << "\n";
            }
            //t = *t.parent;
            //{
            //    auto iteratorFront = gameBoard.solution.begin();
            //    gameBoard.solution.insert(iteratorFront, t);
            //}
            //}
            for (auto node : gameBoard.solution) {
                std::cout << "node: " << node.toString() << "\n";
            }
            return;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    gameBoard.solution.clear();
    return;
}

GameBoard PuzzleSolver::generateRandomGame(std::size_t emptyTiles, std::size_t maxDepth) {
    std::cout << "PuzzleSolver::generateRandomGame\n";
    GameBoard gameBoard{};
    PuzzleSolver puzzleSolver;
    while (true) {
        gameBoard.randomGame(emptyTiles);
        //MoveNode rootNode = puzzleSolver.getTree(gameBoard.serialiseGame(), maxDepth);
        buildTree(gameBoard, maxDepth);
        saveSolution(gameBoard);

        gameBoard.solutionDepth = puzzleSolver.hasASolution(gameBoard.rootNode);
        std::cout << "gameBoard.solution.size(): " << gameBoard.solution.size() << "\n"
                << "solutionDepth: " << gameBoard.solutionDepth << "\n";
        if (gameBoard.solutionDepth > 0)
            return gameBoard;
    }
}

void PuzzleSolver::generateGame(std::size_t emptyTiles, std::size_t maxDepth) {
    //PuzzleSolver puzzleSolver;
    GameBoard gameBoard = generateRandomGame(emptyTiles, maxDepth);
    //MoveNode rootNode = puzzleSolver.getTree(gameBoard.serialiseGame(), maxDepth);
    //int solutionDepth = puzzleSolver.hasASolution(rootNode);
    std::size_t difficulty{0};
    if (gameBoard.solutionDepth > 3) {
        ++difficulty;
    }
    if (gameBoard.solutionDepth > 5) {
        ++difficulty;
    }

    std::cout << "\n{\n\t\"SerializedGame\": \""
            << gameBoard.serialiseGameToString()
            << "\",\n\t\"Difficulty\": " << difficulty
            << ",\n\t\"Par\": " << gameBoard.solutionDepth << "\n},\n";

    /*    int count{0};
        //std::cout << "trying a game: " << ++count << " with emptyTiles: " << emptyTiles << " maxDepth: " << maxDepth;
        do {
            gameBoard.randomGame(emptyTiles);
            MoveNode rootNode = puzzleSolver.getTree(gameBoard.serialiseGame(), maxDepth);
            //std::cout << ".";

            int solutionDepth = puzzleSolver.hasASolution(rootNode);
            if (solutionDepth > 0) {
                std::size_t difficulty{0};
                if (solutionDepth > 3) {
                    ++difficulty;
                }
                if (solutionDepth > 5) {
                    ++difficulty;
                }
                std::cout << "\n{\n\t\"SerializedGame\": \""
                        << gameBoard.serialiseGameToString()
                        << "\",\n\t\"Difficulty\": " << difficulty 
                        << ",\n\t\"Par\": " << solutionDepth << "\n},\n";
                count = -1;
            }
        } while (count > -1); */

}

void PuzzleSolver::generateGames(std::size_t games) {
    while (--games >= 0) {
        std::size_t emptyTiles = (rand() % 13) + 1;
        generateGame(emptyTiles, 3);
    }
}