#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include <vector>
#include "moveNode.h"
#include "solution.h"
#include "direction.h"
#include "gameBoard.h"

namespace SlidingTiles {

    /**
     * @brief A Puzzle Solver class
     */
    class PuzzleSolver {
    public:
        /**
         * @brief My game board
         */
        //GameBoard gameBoard;

        /**
         * @brief returns all moves that are possible on the current gameboard
         */
        std::vector<MoveNode> possibleMoves(const MoveNode & parentNode);

        /**
         * @brief Adds the possibleMoves as MoveNodes to the supplied MoveNode
         * @param moveNode the node on which to Search and add the new Moves
         * @param levels how many levels deep to search 1 .. n
         */
        void addPossibleMoves(MoveNode & moveNode, const int levels);

        /**
         * @brief returns the root node with the whole tree attached to it.
         * @param game The serialised game
         * @param depth The depth to which the tree should be built
         */
        //MoveNode getTree(const std::vector<std::string> & game, int depth = DEFAULT_DEPTH);

        /**
         * @brief returns the root node with the whole tree attached to it.
         * @param game The serialised game
         * @param depth The depth to which the tree should be built
         */
        //MoveNode getTree(const std::wstring & game, int depth = DEFAULT_DEPTH);

        
        /**
         * @brief Builds the tree in the supplied gameBoard
         * @param gameBoard The GameBoard on which to build the tree
         * @param depth The depth to which the tree should be built
         */
        void buildTree(GameBoard & gameBoard, int depth);
        
        /**
         * @brief figures out if the moves tree holds a solution
         * @details Used a breadth-first search to visit all MoveNode nodes. 
         * Since each MoveNode has the endGameState we can load that state
         * into a GameBoard and ask the GameBoard if it is solved.
         * @param node the root node from which to start the search
         * @return the depth at which the node was found or -1 is no solution
         */
        int hasASolution(const MoveNode & node);

        /**
         * @brief figures out if the moves tree holds a solution and stores it 
         * in the supplied gameBoard
         * @details Used a breadth-first search to visit all MoveNode nodes. 
         * Since each MoveNode has the endGameState we can load that state
         * into a GameBoard and ask the GameBoard if it is solved.
         * @param node the root node from which to start the search
         * @return the depth at which the node was found or -1 is no solution
         */
        void saveSolution(GameBoard & gameBoard);
        
        /**
         * Generates a random playable game with a solution depth of Y 0
         * @param emptyTiles The number of empty tiles
         * @param maxDepth The maximum depth to search for 
         * @return the GameBoard of the playable game
         */
        GameBoard generateRandomGame(std::size_t emptyTiles, std::size_t maxDepth);
        
        /**
         * @brief generates a single playable Game and prints it
         * @param emptyTiles The number of empty tiles
         * @param maxDepth The maximum depth for a solution
         */
        void generateGame(std::size_t emptyTiles, std::size_t maxDepth);

        /**
         * @brief generates a series of games
         */
        void generateGames(std::size_t games);

    private:
        /**
         * @brief The number of tiles in each direction
         */
        static const int DEFAULT_DEPTH{3};
    };

} // namespace
