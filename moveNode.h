#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "move.h"
#include <iostream>
#include <string>

namespace SlidingTiles {

    /**
     * @brief A Move with starting state, ending state and child MoveNodes
     */
    class MoveNode : public Move {
    public:

        /**
         * @brief A single step move for a tile at the supplied position in the
         * supplied direction
         * @param startPosition the game board coordinates of the moving tile
         * @param direction the direction to move in
         */
        MoveNode(const sf::Vector2i & startPosition = sf::Vector2i{-1, -1}, const SlidingTiles::Direction & direction = Direction::Unknown)
        : Move(startPosition, direction) {
            id = count;
            ++count;
        };

        /**
         * @brief the depth of the node
         */
        int depth{0};

        /**
         * @brief sets the depth of the node
         * @param newDepth the depth of the node
         */
        void setDepth(int newDepth) {
            depth = newDepth;
        }

        /**
         * @brief a pointer to the parent MoveNode, defaults to nullptr
         */
        const MoveNode * parent {nullptr};
        
        /**
         * @brief rsets the parent of this MoveNode
         * @param parentNode the new parent node
         */
        void setParent( const MoveNode & parentNode ) {
            //std::cout << "Setting parent on node #" << id << " to #" << parentNode.id << "\n";
            parent = &parentNode;
        }
        
        /**
         * @brief ending board (serialised)
         */
        std::vector <std::string> endingBoard{};

        /**
         * @brief sets the ending board state
         */
        void setEndingBoard(const std::vector <std::string> & serialisedGame) {
            endingBoard = serialisedGame;
        }

        /**
         * @brief The vector with all possible child moves
         */
        std::vector <MoveNode> possibleMoves{};

        /**
         * @brief explains the move
         */
        std::string toString(const int & indent) {
            std::stringstream ss;
            ss << std::string(indent, ' ') << "Move #" << id
                    << " startPosition: [" << startPosition.x
                    << "][" << startPosition.y << "]" << " depth: " << depth
                    << " direction: " << directionToString(direction)
                    << " possibleMoves: " << possibleMoves.size() ; //<< "\n";
            //ss << std::string(indent, ' ');
            ss << " parent: ";
            if ( parent == nullptr ) {
                ss << "nullptr";
            } else {
                ss << " #" << parent->id;
            }
            ss << " endingBoard: ";
            for (std::string s : endingBoard) {
                ss << s;
            }
            ss << "\n";
            for (int i = 0; i < possibleMoves.size(); ++i) {
                ss << std::string(indent, ' ') << "possibleMove[" << i << "] -->\n";
                ss << possibleMoves[i].toString(indent + 2);
            }
            return ss.str();
        }

        /**
         * @brief print the solution
         */
        std::string enumerateMoves() {
            std::vector<std::string> output;

            const MoveNode * movePtr = this;

            do {
                std::stringstream ss;
                ss << "{\"x\":" << movePtr->startPosition.x
                    << ",\"y\":" << movePtr->startPosition.y << ",\"Direction\":\"" << directionToString(movePtr->direction)
                    << "\"}";

                output.push_back(ss.str());
                movePtr = movePtr->parent;
            } while ( movePtr != nullptr );

            std::string out{"\t\"Solution\":["};
            for (unsigned i = output.size()-1; i-- > 0; ) {
                out += output.at(i);
                if (i) { out += ","; }
            }
            out += "],\n";
            out += "\t\"Par\":";
            out += std::to_string( output.size()-1 );
            return out;
        }

        /**
         * @brief explains the move
         */
        virtual std::string toString() {
            return toString(0);
        }

        /**
         * @brief counter
         */
        static int count;

        /**
         * @brief My id
         */
        int id;

    };

} // namespace SlidingTiles
