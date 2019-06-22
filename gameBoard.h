#pragma once

#include "moveNode.h"
#include "tile.h"
#include "zmqSingleton.h"
#include <stdexcept>      // std::out_of_range
#include <vector>

namespace SlidingTiles {

    /**
     * @brief A Game board
     */
    class GameBoard {
    public:
        /**
         * @brief The number of tiles in each direction
         */
        static const int boardSize{4};

        /**
         * @brief returns a pointer to the tile at the indicated coordinates
         */
        Tile* getTile(const unsigned int x, const unsigned int y) {
            if ( x >= boardSize || y >= boardSize ) {
                throw std::out_of_range{"Bad board coordinates requested"};
            } else {
                return &tiles[x][y];
            }
        }

        /**
         * @brief The 2d array of tiles that makes up the game board
         */
        Tile tiles [boardSize][boardSize];

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::string game[boardSize][boardSize]);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::vector<std::string> & game);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::wstring & game);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::string & game);

        /**
         * @brief sets up a random game by placing random tiles on the board.
         *        Games that are directly solved without moving a tile are 
         *        discarded.
         * @param emptyTiles the number of empty tiles to place defaults to 3
         * @throws a runtime_error if we can't get a non-solved game board placed after 200 tries
         */
        void randomGame(const int emptyTiles = 3);


        /**
         * @brief saves the game into an vector of string characters
         */
        std::vector<std::string> serialiseGame();

        /**
         * @brief saves the game into a string;
         */
        std::string serialiseGameToString();

        /**
         * @brief prints the game to the console
         */
        void printGame();

        /**
         * @brief Returns the adjacent tile in the supplied direction and check for off-the board condition.
         * If no adjacent tile is possible it returns -1,-1
         * @param move The position of the tile to query and the direction
         */
        sf::Vector2i getAdjacentTilePosition(const Move & move);

        /**
         * @brief return whether the move is possible
         * @param move the position of the tile to move and the direction in which to move it
         * @return true if a slide is allowed, false if not
         */
        bool canSlideTile(const Move & move);

        /**
         * @brief slides the tile from the movingTilePosition to the newPosition 
         * with a transition command if this is legal. Since the target position 
         * must have been an empty tile it is pushed over to the position that 
         * is vacated. 
         * @param move The movement
         */
        void slideTile(const Move & move);

        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns nullptr
         */
        const Tile* findStartTile();

        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns -1,-1
         */
        sf::Vector2i findEndTile();

        /**
         * @brief Used to find a solution by returning the output tile if we 
         * roll a ball into the tile from the supplied direction.
         * If we hit a matching end tile it returns -2,-2. If we can't end properly 
         * because of an off the board or empty tile we return -1,-1
         * @param move The move to for the ball
         */
        sf::Vector2i getOutputPosition(const Move & move);

        /**
         * @brief Returns the next move after the supplied move
         * If we hit a matching end tile it returns -2,-2. If we can't end properly 
         * because of an off the board or empty tile we return -1,-1
         * @param move The move to for the ball
         */
        Move getOutputMove(const Move & move);

        /**
         * @brief returns if the puzzle is in a solved state by checking the path
         * from the start tile to the end tile.
         * @return a vector with the tile positions of the solution if solved otherwise 
         * returns an empty vector
         */
        const std::vector<sf::Vector2i> isSolved();

        /**
         * @brief The puzzleSolver can use this to store the tree
         */
        MoveNode rootNode{};

        /**
         * @brief The puzzleSolver can put the cheapest solution here
         */
        std::vector<Move> solution{};

    private:
        /** 
         * @brief picks start tile that works on the board.
         * @throws a runtime_error if there is a problem placing the tile
         */
        Tile pickStartTile(const sf::Vector2i & startPos);

        /** 
         * @brief picks an end tile that works on the board.
         * @throws a runtime_error if there is a problem placing the tile
         */
        Tile pickEndTile(const sf::Vector2i & endPos);


        /**
         * @brief sets up a random game by placing random tiles on the board.
         * @param emptyTiles the number of empty tiles to place defaults to 3
         */
        void randomGameImpl(const int emptyTiles = 3);

    };

} // namespace