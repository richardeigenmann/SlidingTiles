#pragma once
#include <string>

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

/**
 * @brief Returns a string of the tile type.
 * @param t the tile type to convert
 */
std::string tileTypeToString(const TileType & t);

/**
 * @brief Returns the tile type from the supplied string. If it doesn't match
 * it returns TileType::Empty
 * @param s the string to parse
 * @return the tileType or TileType::Empty if no match
 */
TileType stringToTileType(const std::string & s);

/**
 * @brief Returns a char for the tile type. Used for Serialisation
 */
std::string tileTypeToChar(const TileType & t);

/**
 * @brief Returns a char for the tile type. Used for Serialisation
 */
std::wstring tileTypeToWstringChar(const TileType & t);


/**
 * @brief Returns if a TileType is a start tile 
 */
bool isStartTileType(const TileType & t);

/**
 * @brief Returns if a random start TileType
 */
TileType randomStartTileType();


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isEndTileType(const TileType & t);


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isMoveableType(const TileType & t);

/**
 * @brief Returns if a random end TileType
 */
TileType randomEndTileType();

/**
 * @brief Returns if a tile is a game TileType
 */
bool isGameTileType(const TileType & t);


/**
 * @brief Returns a random game TileType
 */
TileType randomGameTileType();// NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK