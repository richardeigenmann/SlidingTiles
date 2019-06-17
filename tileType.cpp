#include "tileType.h"
#include <array>

std::string tileTypeToString(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Empty";
        case TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Horizontal";
        case TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Vertical";
        case TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartTop";
        case TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartBottom";
        case TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartLeft";
        case TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartRight";
        case TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndTop";
        case TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndBottom";
        case TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndRight";
        case TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndLeft";
        case TileType::LeftTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "LeftTop";
        case TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "LeftBottom";
        case TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "TopRight";
        case TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "BottomRight";
        case TileType::Obstacle:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Obstacle";
        default:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Unknown Type";
    }
}

TileType stringToTileType(const std::string & s) {
    if (s == "Horizontal") {
        return TileType::Horizontal;
    } 
    if (s == "Vertical") {
        return TileType::Vertical;
    } 
    if (s == "StartTop") {
        return TileType::StartTop;
    } 
    if (s == "StartBottom") {
        return TileType::StartBottom;
    } 
    if (s == "StartLeft") {
        return TileType::StartLeft;
    } 
    if (s == "StartRight") {
        return TileType::StartRight;
    } 
    if (s == "EndTop") {
        return TileType::EndTop;
    } 
    if (s == "EndBottom") {
        return TileType::EndBottom;
    } 
    if (s == "EndRight") {
        return TileType::EndRight;
    } 
    if (s == "EndLeft") {
        return TileType::EndLeft;
    } 
    if (s == "LeftTop") {
        return TileType::LeftTop;
    } 
    if (s == "LeftBottom") {
        return TileType::LeftBottom;
    } 
    if (s == "TopRight") {
        return TileType::TopRight;
    } 
    if (s == "BottomRight") {
        return TileType::BottomRight;
    } 
    if (s == "Obstacle") {
        return TileType::Obstacle;
    } 
    return TileType::Empty;  
}

// TODO: Why to Char and return a String??
std::string tileTypeToChar(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return " ";
        case TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "-";
        case TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "|";
        case TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┴";
        case TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┬";
        case TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┤";
        case TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "├";
        case TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┻";
        case TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┳";
        case TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┣";
        case TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┫";
        case TileType::LeftTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┘";
        case TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┐";
        case TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "└";
        case TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┌";
        case TileType::Obstacle:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "o";
        default:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "?";
    }
}

std::wstring tileTypeToWstringChar(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L" ";
        case TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"-";
        case TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"|";
        case TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┴";
        case TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┬";
        case TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┤";
        case TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"├";
        case TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┻";
        case TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┳";
        case TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┣";
        case TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┫";
        case TileType::LeftTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┘";
        case TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┐";
        case TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"└";
        case TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┌";
        case TileType::Obstacle:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"o";
        default:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"?";
    }
}

/**
 * @brief Returns if a TileType is a start tile 
 */
bool isStartTileType(const TileType & t) {
    switch (t) {
        case TileType::StartTop:
            return true;
        case TileType::StartBottom:
            return true;
        case TileType::StartLeft:
            return true;
        case TileType::StartRight:
            return true;
        default:
            return false;
    }
}


const std::array<TileType,4> START_TILES {TileType::StartTop, TileType::StartBottom, TileType::StartLeft, TileType::StartRight};

/**
 * @brief Returns if a random start TileType
 */
TileType randomStartTileType() {
    return START_TILES.at(random() % START_TILES.size());
}


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isEndTileType(const TileType & t) {
    switch (t) {
        case TileType::EndTop:
            return true;
        case TileType::EndBottom:
            return true;
        case TileType::EndLeft:
            return true;
        case TileType::EndRight:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Returns if a TileType is moveable
 */
bool isMoveableType(const TileType & t) {
    return !  (t == TileType::Empty || t == TileType::Obstacle || isStartTileType( t ) ||  isEndTileType( t ));
}


const std::array<TileType,4> END_TILES {TileType::EndTop, TileType::EndBottom, TileType::EndLeft, TileType::EndRight};

/**
 * @brief Returns if a random end TileType
 */
TileType randomEndTileType() {
    return END_TILES.at(random() % END_TILES.size());
}

bool isGameTileType(const TileType & t) {
    switch (t) {
        case TileType::Horizontal:
            return true;
        case TileType::Vertical:
            return true;
        case TileType::LeftTop:
            return true;
        case TileType::LeftBottom:
            return true;
        case TileType::TopRight:
            return true;
        case TileType::BottomRight:
            return true;
        default:
            return false;

    }
}

const std::array<TileType,7> GAME_TILES {TileType::Horizontal, TileType::Vertical, 
    TileType::LeftTop, TileType::LeftBottom, TileType::TopRight, 
    TileType::BottomRight, TileType::Obstacle};

TileType randomGameTileType() {
    return GAME_TILES.at(random() % GAME_TILES.size());
}