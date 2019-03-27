#include "gameBoard.h"
#include <stdlib.h> // srand, rand
#include <algorithm> // std::shuffle
#include <random> // random_shuffle, std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <assert.h> // assert
#include <sstream> // stringstream
#include <locale>
#include <codecvt>
#include "json.hpp"
#include <stdexcept>
#include "tileType.h"

using namespace SlidingTiles;
using json = nlohmann::json;

const int GameBoard::boardSize;

void GameBoard::loadGame(const std::string game[boardSize][boardSize]) {
    for (int x = 0; x < boardSize; ++x) {
        for (int y = 0; y < boardSize; ++y) {
            Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y][x]); // note the inversion here!
            //std::cout << "[" << x << "][" << y << "] char: " << game[x][y] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::SET_TILE;
            jsonMessage["position"]["x"] = x;
            jsonMessage["position"]["y"] = y;
            jsonMessage["tileType"] = tileTypeToString(tile->getTileType());
            ZmqSingleton::getInstance().publish(jsonMessage);
        }
    }
    solution.clear();
}

void GameBoard::loadGame(const std::vector<std::string> & game) {
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y * 4 + x]);
            //std::cout << "[" << x << "][" << y << "] game[y*4+x]: " << game[y*4+x] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::SET_TILE;
            jsonMessage["position"]["x"] = x;
            jsonMessage["position"]["y"] = y;
            jsonMessage["tileType"] = tileTypeToString(tile->getTileType());
            ZmqSingleton::getInstance().publish(jsonMessage);
        }
    }
    solution.clear();
}

void GameBoard::loadGame(const std::wstring & game) {
    assert(game.size() == boardSize * boardSize);
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(std::wstring{game[y * 4 + x]});
            //std::wcout << L"[" << x << L"][" << y << L"] game[y*4+x]: " << std::wstring{game[y * 4 + x]} << L" became: \"" << tileTypeToWstringChar(tile->getTileType()) << L"\"\n";
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::SET_TILE;
            jsonMessage["position"]["x"] = x;
            jsonMessage["position"]["y"] = y;
            jsonMessage["tileType"] = tileTypeToString(tile->getTileType());
            ZmqSingleton::getInstance().publish(jsonMessage);
        }
    }
    solution.clear();
}

void GameBoard::loadGame(const std::string & game) {
    std::u16string utf16 = std::wstring_convert < std::codecvt_utf8_utf16<char16_t>, char16_t>{}
    .from_bytes(game.data());
    assert(utf16.size() >= boardSize * boardSize);

    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(std::wstring{utf16[y * 4 + x]});
            //std::wcout << L"[" << x << L"][" << y << L"] game[y*4+x]: " << std::wstring{game[y * 4 + x]} << L" became: \"" << tileTypeToWstringChar(tile->getTileType()) << L"\"\n";
            json jsonMessage{};
            jsonMessage["state"] = ZmqSingleton::SET_TILE;
            jsonMessage["position"]["x"] = x;
            jsonMessage["position"]["y"] = y;
            jsonMessage["tileType"] = tileTypeToString(tile->getTileType());
            ZmqSingleton::getInstance().publish(jsonMessage);
        }
    }
    solution.clear();
}

void GameBoard::randomGame(const int emptyTiles) {
    for (size_t passes=0; passes<200; ++passes) {
        randomGameImpl(emptyTiles);
        if ( isSolved().empty() ) {
            solution.clear();
            return;
        } 
        std::cout << "No good. Already solved. Trying again.\n";
    }
    throw std::runtime_error("Something is terribly wrong. We rendered 200 game boards and got a solved board 200 times? What a conincidence...");
}

Tile GameBoard::pickStartTile(const sf::Vector2i & startPos) {
    Tile startTile{};
    startTile.setTilePosition(startPos);
    TileType type = randomStartTileType();
    // correct tiles that don't work
    if (startPos.x == 0 && type == TileType::StartLeft) {
        // can't go left on column 0
        type = TileType::StartRight;
    } else if (startPos.y == 0 && type == TileType::StartTop) {
        // can't go up on row 0
        type = TileType::StartBottom;
    } else if (startPos.x == boardSize-1 && type == TileType::StartRight) {
        // can't go right on right column
        type = TileType::StartLeft;
    } else if (startPos.y == boardSize-1 && type == TileType::StartBottom) {
        // can't go down on bottom row
        type = TileType::StartTop;
    }
    startTile.setTileType(type);
    return startTile;
}


Tile GameBoard::pickEndTile(const sf::Vector2i & endPos) {
    Tile endTile{};
    endTile.setTilePosition(endPos);
    TileType type = randomEndTileType();
    // correct tiles that don't work
    if (endPos.x == 0 && type == TileType::EndLeft) {
        // can't come from left on column 0
        type = TileType::EndRight;
    } else if (endPos.y == 0 && type == TileType::EndTop) {
        // can't come from top on row 0
        type = TileType::EndBottom;
    } else if (endPos.x == boardSize-1 && type == TileType::EndRight) {
        // can't come from right on right column
        type = TileType::EndLeft;
    } else if (endPos.y == boardSize-1 && type == TileType::EndBottom) {
        // can't go up to bottom row
        type = TileType::EndTop;
    }
    endTile.setTileType(type);
    return endTile;
}

void GameBoard::randomGameImpl(const int emptyTiles) {
    assert(emptyTiles > 0 && emptyTiles < boardSize * boardSize - 2);
    std::cout << "Setting up a random board\n";

    std::vector<sf::Vector2i> positions{};
    for (int x = 0; x < boardSize; ++x) {
        for (int y = 0; y < boardSize; ++y) {
            positions.push_back(sf::Vector2i{x, y});
        }
    }
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd{};
    std::shuffle(std::begin(positions), std::end(positions), std::default_random_engine(rd()));

    sf::Vector2i startPos = positions[0];
    tiles[startPos.x][startPos.y] = pickStartTile(startPos);

    sf::Vector2i endPos = positions[1];
    tiles[endPos.x][endPos.y] = pickEndTile(endPos);

    for (int i = 0; i < emptyTiles; ++i) {
        sf::Vector2i emptyPos = positions[2 + i];
        Tile emptyTile{};
        emptyTile.setTilePosition(emptyPos);
        emptyTile.setTileType(TileType::Empty);
        tiles[emptyPos.x][emptyPos.y] = emptyTile;
    }

    int totalTiles = boardSize * boardSize;
    for (int i = 2 + emptyTiles; i < totalTiles; ++i) {
        TileType tileType{TileType::Empty};
        switch (rand() % 6) {
            case 0: tileType = TileType::Horizontal;
                break;
            case 1: tileType = TileType::Vertical;
                break;
            case 2: tileType = TileType::LeftTop;
                break;
            case 3: tileType = TileType::LeftBottom;
                break;
            case 4: tileType = TileType::TopRight;
                break;
            case 5: tileType = TileType::BottomRight;
                break;
        }
        sf::Vector2i tilePos = positions[i];
        Tile tile{};
        tile.setTilePosition(tilePos);
        tile.setTileType(tileType);
        tiles[tilePos.x][tilePos.y] = tile;
    }
}

std::vector<std::string> GameBoard::serialiseGame() {
    std::vector<std::string> serialisedGame;
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            serialisedGame.push_back(tileTypeToChar(tiles[x][y].getTileType()));
        }
    }
    return serialisedGame;
}

std::string GameBoard::serialiseGameToString() {
    std::stringstream ss;
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            ss << tileTypeToChar(tiles[x][y].getTileType());
        }
    }
    return ss.str();
}

void GameBoard::printGame() {
    std::cout << serialiseGameToString() << std::endl;
}

sf::Vector2i GameBoard::getAdjacentTilePosition(const Move & move) {
    // TODO should this not be a function of the move?
    assert(move.startPosition.x >= 0 && move.startPosition.x < boardSize);
    assert(move.startPosition.y >= 0 && move.startPosition.y < boardSize);
    sf::Vector2i adjacentPosition{move.startPosition.x, move.startPosition.y};

    if (move.direction == Direction::GoDown) {
        ++adjacentPosition.y;
    } else { 
        if (move.direction == Direction::GoUp) {
           --adjacentPosition.y;
        } else {
            if (move.direction == Direction::GoLeft) {
                --adjacentPosition.x;
            } else { 
                if (move.direction == Direction::GoRight) {
                    ++adjacentPosition.x;
                }
            }
        }
    }


    if (adjacentPosition.x < 0 || adjacentPosition.y < 0 || adjacentPosition.x >= boardSize || adjacentPosition.y >= boardSize) {
        adjacentPosition.x = -1;
        adjacentPosition.y = -1;
    }
    return adjacentPosition;
}

bool GameBoard::canSlideTile(const Move & move) {
    assert(move.startPosition.x >= 0 && move.startPosition.x < boardSize);
    assert(move.startPosition.y >= 0 && move.startPosition.y < boardSize);
    Tile movingTile = tiles[move.startPosition.x][move.startPosition.y];
    /*std::cout << "canSlideTile: [" << move.startPosition.x << "][" << move.startPosition.y
             << "] Direction: " << directionToString(move.direction) << "\n";*/
    if (!movingTile.isMoveable) {
        return false;
    }

    sf::Vector2i newPosition = getAdjacentTilePosition(move);
    // check for move off the board
    if (newPosition.x >= boardSize
            || newPosition.y >= boardSize
            || newPosition.x < 0
            || newPosition.y < 0) {
        return false;
    }

    // check if newPosition already taken
    if (tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty) {
        return false;
    }

    return true;
}

void GameBoard::slideTile(const Move & move) {
    assert(move.startPosition.x >= 0 && move.startPosition.x < boardSize);
    assert(move.startPosition.y >= 0 && move.startPosition.y < boardSize);
    if (canSlideTile(move)) {
        sf::Vector2i newPosition = getAdjacentTilePosition(move);
        Tile slidingTile = tiles[move.startPosition.x][move.startPosition.y];
        Tile obscuredTile = tiles[newPosition.x][newPosition.y];

        slidingTile.transition(newPosition);
        obscuredTile.setTilePosition(move.startPosition);


        json jsonMessage{};
        jsonMessage["state"] = ZmqSingleton::SLIDE_TILE;
        jsonMessage["startPosition"]["x"] = move.startPosition.x;
        jsonMessage["startPosition"]["y"] = move.startPosition.y;
        jsonMessage["newPosition"]["x"] = newPosition.x;
        jsonMessage["newPosition"]["y"] = newPosition.y;
        ZmqSingleton::getInstance().publish(jsonMessage);

        tiles[newPosition.x][newPosition.y] = slidingTile;
        tiles[move.startPosition.x][move.startPosition.y] = obscuredTile;
    }
    solution.clear();
}

const Tile GameBoard::findStartTile() {
    for (int x = 0; (x < boardSize); ++x) {
        for (int y = 0; (y < boardSize); ++y) {
            if (isStartTileType(tiles[x][y].getTileType())) {
                return tiles[x][y];
            }
        }
    }

    Tile errorTile{};
    errorTile.setTilePosition(sf::Vector2i{-1, -1});
    return errorTile;
}

sf::Vector2i GameBoard::getOutputPosition(const Move & move) {
    assert(move.startPosition.x >= 0 && move.startPosition.x < boardSize);
    assert(move.startPosition.y >= 0 && move.startPosition.y < boardSize);
    TileType type = tiles[move.startPosition.x][move.startPosition.y].getTileType();
    sf::Vector2i nextTile{move.startPosition.x, move.startPosition.y};

    if (type == TileType::StartRight && move.startPosition.x < boardSize - 1) {
        ++nextTile.x;
    } else if (type == TileType::StartLeft && move.startPosition.x < boardSize - 1 && move.startPosition.x > 0) {
        --nextTile.x;
    } else if (type == TileType::StartTop && move.startPosition.y > 0) {
        --nextTile.y;
    } else if (type == TileType::StartBottom && move.startPosition.y < boardSize - 1) {
        ++nextTile.y;
    } else if (type == TileType::Horizontal && move.startPosition.x < boardSize - 1 && move.direction == Direction::GoRight) {
        ++nextTile.x;
    } else if (type == TileType::Horizontal && move.startPosition.x > 0 && move.direction == Direction::GoLeft) {
        --nextTile.x;
    } else if (type == TileType::Vertical && move.startPosition.y < boardSize - 1 && move.direction == Direction::GoDown) {
        ++nextTile.y;
    } else if (type == TileType::Vertical && move.startPosition.y > 0 && move.direction == Direction::GoUp) {
        --nextTile.y;
    } else if (type == TileType::LeftBottom && move.startPosition.y < boardSize - 1 && move.direction == Direction::GoRight) {
        ++nextTile.y;
    } else if (type == TileType::LeftBottom && move.startPosition.x > 0 && move.direction == Direction::GoUp) {
        --nextTile.x;
    } else if (type == TileType::LeftTop && move.startPosition.x > 0 && move.direction == Direction::GoDown) {
        --nextTile.x;
    } else if (type == TileType::LeftTop && move.startPosition.y > 0 && move.direction == Direction::GoRight) {
        --nextTile.y;
    } else if (type == TileType::BottomRight && move.startPosition.x < boardSize - 1 && move.direction == Direction::GoUp) {
        ++nextTile.x;
    } else {
        if (type == TileType::BottomRight && move.startPosition.y < boardSize - 1 && move.direction == Direction::GoLeft) {
            ++nextTile.y;
        } else {
            if (type == TileType::TopRight && move.startPosition.y > 0 && move.direction == Direction::GoLeft) {
                --nextTile.y;
            } else {
                if (type == TileType::TopRight && move.startPosition.x < boardSize - 1 && move.direction == Direction::GoDown) {
                    ++nextTile.x;
                } else {
                    if ((type == TileType::EndBottom && move.direction == Direction::GoUp)
                        || (type == TileType::EndLeft && move.direction == Direction::GoRight)
                        || (type == TileType::EndRight && move.direction == Direction::GoLeft)
                        || (type == TileType::EndTop && move.direction == Direction::GoDown)) {
                        nextTile.x = -2;
                        nextTile.y = -2;
                    } else {
                        nextTile.x = -1;
                        nextTile.y = -1;
                    }
                }
            }
        }
    }

    assert(nextTile.x >= -2 && nextTile.x < boardSize);
    assert(nextTile.y >= -2 && nextTile.y < boardSize);
    return nextTile;
}

Move GameBoard::getOutputMove(const Move & move) {
    assert(move.startPosition.x >= 0 && move.startPosition.x < boardSize);
    assert(move.startPosition.y >= 0 && move.startPosition.y < boardSize);
    Tile startTile = tiles[move.startPosition.x][move.startPosition.y];
    Move outputMove{getOutputPosition(move), startTile.outputDirection(move.direction)};
    assert(outputMove.startPosition.x >= -2 && outputMove.startPosition.x < boardSize);
    assert(outputMove.startPosition.y >= -2 && outputMove.startPosition.y < boardSize);
    return outputMove;
}

std::vector<sf::Vector2i> GameBoard::isSolved() {
    std::vector<sf::Vector2i> solutionPath{};

    Tile startTile = findStartTile();
    if (startTile.getTilePosition().x == -1) { return solutionPath; } // no start tile
    solutionPath.push_back(startTile.getTilePosition());

    Move move{startTile.getTilePosition(), startTile.outputDirection(Direction::Unknown)};
    int count{0};
    while (move.startPosition.x >= 0 && ++count < boardSize * boardSize) {
        move = getOutputMove(move);
        if (move.startPosition.x >= 0) {
            solutionPath.push_back(move.startPosition);
        }
    }

    if (move.startPosition.x != -2) {
        solutionPath = {};
    }
    return solutionPath;
}

