#pragma once

#include "direction.h"
#include "gameBoard.h"
#include "moveNode.h"
#include "solution.h"
#include <random>

#include "gameSettings.h"

namespace SlidingTiles
{

/**
     * @brief A Puzzle Solver class
     */
class PuzzleSolver
{
public:
    PuzzleSolver() {
        // see Book Marius Bancila Modern C++ Programming Cookbook
        std::random_device rd{};
        randomNumberGenerator.seed(rd());
        const unsigned int MAXIMUM_EMPTY_TILES {13};
        auto ud = std::uniform_int_distribution<>{1, MAXIMUM_EMPTY_TILES};
    }

     auto static checkTileDirections(MoveNode &moveNode, GameBoard &gameBoard, sf::Vector2i position) -> std::optional<SlidingTiles::MoveNode>;

    /**
         * @brief returns all moves that are possible on the current gameboard
         */
    auto static possibleMoves(MoveNode &moveNode) -> std::optional<MoveNode>;

    /**
         * @brief Adds the possibleMoves as MoveNodes to the supplied MoveNode
         * @param moveNode the node on which to Search and add the new Moves
         * @param levels how many levels deep to search 1 .. n
         */
    auto static addPossibleMoves(MoveNode &moveNode, const size_t levels) -> std::optional<MoveNode>;

    /**
         * @brief Builds the tree in the supplied gameBoard
         * @param gameBoard The GameBoard on which to build the tree
         * @param depth The depth to which the tree should be built
         */
    auto static buildTree(GameBoard &gameBoard, size_t depth) -> std::optional<MoveNode>;

    /**
         * @brief saves the solution to the supplied GameBoard
         * @param gameBoard the GameBoard to which the solution is to be saved
         */
    static void saveSolution(GameBoard &gameBoard);

    /**
         * Generates a random playable game
         * @param settings The number of empty tiles and the maximum depth to search for
         * @return the GameBoard of the playable game
         */
    auto static generateRandomGame(GameSettings settings) -> GameBoard;

    auto static generateRandomGameBoardAndSolution(GameSettings settings) -> std::tuple<SlidingTiles::GameBoard, std::optional<SlidingTiles::MoveNode>>;

    /**
         * @brief generates a series of games
         * @param games The number of games to generate
         */
    void generateGames(std::size_t games);

private:
    /**
         * @brief The number of tiles in each direction
         */
    static const int DEFAULT_DEPTH{3};

    /**
         * @brief add a decent random number Generator to the class
         */
    std::mt19937 randomNumberGenerator;

    /**
     * @brief a uniform distribution of 1 to 13 empty tiles
     */
    std::uniform_int_distribution<std::mt19937::result_type> ud;
};

} // namespace SlidingTiles
