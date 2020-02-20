#pragma once
#include <string>

namespace SlidingTiles {

enum class TileType {
    Empty,
    Horizontal,
    Vertical,
    StartTop,
    StartBottom,
    StartLeft,
    StartRight,
    EndTop,
    EndBottom,
    EndRight,
    EndLeft,
    LeftTop,
    LeftBottom,
    TopRight,
    BottomRight,
    Obstacle
};
} // namespace Sliding Tiles

/**
 * @brief Returns a string of the tile type.
 * @param t the tile type to convert
 */
std::string tileTypeToString(const SlidingTiles::TileType & t);

/**
 * @brief Returns the tile type from the supplied string. If it doesn't match
 * it returns TileType::Empty
 * @param s the string to parse
 * @return the tileType or TileType::Empty if no match
 */
SlidingTiles::TileType stringToTileType(const std::string & s);

/**
 * @brief Returns a char for the tile type. Used for Serialisation
 */
//std::string tileTypeToChar(const SlidingTiles::TileType & t);

/**
 * @brief Returns a char for the tile type. Used for Serialisation
 */
std::wstring tileTypeToWstringChar(const SlidingTiles::TileType & t);


/**
 * @brief Returns if a TileType is a start tile 
 */
bool isStartTileType(const SlidingTiles::TileType & t);

/**
 * @brief Returns if a random start TileType
 */
SlidingTiles::TileType randomStartTileType();


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isEndTileType(const SlidingTiles::TileType & t);


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isMoveableType(const SlidingTiles::TileType & t);

/**
 * @brief Returns if a random end TileType
 */
SlidingTiles::TileType randomEndTileType();

/**
 * @brief Returns if a tile is a game TileType
 */
bool isGameTileType(const SlidingTiles::TileType & t);

/**
 * @brief Returns a random game TileType
 */
SlidingTiles::TileType randomGameTileType();