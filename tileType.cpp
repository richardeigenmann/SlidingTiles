#include "tileType.h"
#include <array>

auto tileTypeToString(const SlidingTiles::TileType & t) -> std::string {
    switch (t) {
        case SlidingTiles::TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Empty";
        case SlidingTiles::TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Horizontal";
        case SlidingTiles::TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Vertical";
        case SlidingTiles::TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartTop";
        case SlidingTiles::TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartBottom";
        case SlidingTiles::TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartLeft";
        case SlidingTiles::TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "StartRight";
        case SlidingTiles::TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndTop";
        case SlidingTiles::TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndBottom";
        case SlidingTiles::TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndRight";
        case SlidingTiles::TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "EndLeft";
        case SlidingTiles::TileType::LeftTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "LeftTop";
        case SlidingTiles::TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "LeftBottom";
        case SlidingTiles::TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "TopRight";
        case SlidingTiles::TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "BottomRight";
        case SlidingTiles::TileType::Obstacle:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Obstacle";
        default:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "Unknown Type";
    }
}

auto stringToTileType(const std::string & s) -> SlidingTiles::TileType {
    if (s == "Horizontal") {
        return SlidingTiles::TileType::Horizontal;
    } 
    if (s == "Vertical") {
        return SlidingTiles::TileType::Vertical;
    } 
    if (s == "StartTop") {
        return SlidingTiles::TileType::StartTop;
    } 
    if (s == "StartBottom") {
        return SlidingTiles::TileType::StartBottom;
    } 
    if (s == "StartLeft") {
        return SlidingTiles::TileType::StartLeft;
    } 
    if (s == "StartRight") {
        return SlidingTiles::TileType::StartRight;
    } 
    if (s == "EndTop") {
        return SlidingTiles::TileType::EndTop;
    } 
    if (s == "EndBottom") {
        return SlidingTiles::TileType::EndBottom;
    } 
    if (s == "EndRight") {
        return SlidingTiles::TileType::EndRight;
    } 
    if (s == "EndLeft") {
        return SlidingTiles::TileType::EndLeft;
    } 
    if (s == "LeftTop") {
        return SlidingTiles::TileType::LeftTop;
    } 
    if (s == "LeftBottom") {
        return SlidingTiles::TileType::LeftBottom;
    } 
    if (s == "TopRight") {
        return SlidingTiles::TileType::TopRight;
    } 
    if (s == "BottomRight") {
        return SlidingTiles::TileType::BottomRight;
    } 
    if (s == "Obstacle") {
        return SlidingTiles::TileType::Obstacle;
    } 
    return SlidingTiles::TileType::Empty;  
}

// TODO(richi): Why to Char and return a String??
auto tileTypeToChar(const SlidingTiles::TileType & t) -> std::string {
    switch (t) {
        case SlidingTiles::TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return " ";
        case SlidingTiles::TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "-";
        case SlidingTiles::TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "|";
        case SlidingTiles::TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┴";
        case SlidingTiles::TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┬";
        case SlidingTiles::TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┤";
        case SlidingTiles::TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "├";
        case SlidingTiles::TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┻";
        case SlidingTiles::TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┳";
        case SlidingTiles::TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┣";
        case SlidingTiles::TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┫";
        case SlidingTiles::TileType::LeftTop:
            // SlidingTiles::NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┘";
        case SlidingTiles::TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┐";
        case SlidingTiles::TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "└";
        case SlidingTiles::TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "┌";
        case SlidingTiles::TileType::Obstacle:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "o";
        default:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return "?";
    }
}

auto tileTypeToWstringChar(const SlidingTiles::TileType & t) -> std::wstring {
    switch (t) {
        case SlidingTiles::TileType::Empty:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L" ";
        case SlidingTiles::TileType::Horizontal:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"-";
        case SlidingTiles::TileType::Vertical:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"|";
        case SlidingTiles::TileType::StartTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┴";
        case SlidingTiles::TileType::StartBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┬";
        case SlidingTiles::TileType::StartLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┤";
        case SlidingTiles::TileType::StartRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"├";
        case SlidingTiles::TileType::EndTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┻";
        case SlidingTiles::TileType::EndBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┳";
        case SlidingTiles::TileType::EndRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┣";
        case SlidingTiles::TileType::EndLeft:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┫";
        case SlidingTiles::TileType::LeftTop:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┘";
        case SlidingTiles::TileType::LeftBottom:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┐";
        case SlidingTiles::TileType::TopRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"└";
        case SlidingTiles::TileType::BottomRight:
            // NOLINTNEXTLINE (fuchsia-default-arguments) Default allocator for String is OK
            return L"┌";
        case SlidingTiles::TileType::Obstacle:
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
auto isStartTileType(const SlidingTiles::TileType & t) -> bool {
    switch (t) {
        case SlidingTiles::TileType::StartTop:
            return true;
        case SlidingTiles::TileType::StartBottom:
            return true;
        case SlidingTiles::TileType::StartLeft:
            return true;
        case SlidingTiles::TileType::StartRight:
            return true;
        default:
            return false;
    }
}


const std::array<SlidingTiles::TileType,4> START_TILES {
    SlidingTiles::TileType::StartTop, SlidingTiles::TileType::StartBottom, 
    SlidingTiles::TileType::StartLeft, SlidingTiles::TileType::StartRight};

/**
 * @brief Returns if a random start TileType
 */
auto randomStartTileType() -> SlidingTiles::TileType {
    return START_TILES.at(random() % START_TILES.size());
}


/**
 * @brief Returns if a TileType is an end tile 
 */
auto isEndTileType(const SlidingTiles::TileType & t) -> bool {
    switch (t) {
        case SlidingTiles::TileType::EndTop:
            return true;
        case SlidingTiles::TileType::EndBottom:
            return true;
        case SlidingTiles::TileType::EndLeft:
            return true;
        case SlidingTiles::TileType::EndRight:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Returns if a TileType is moveable
 */
auto isMoveableType(const SlidingTiles::TileType & t) -> bool {
    return !  (t == SlidingTiles::TileType::Empty || t == SlidingTiles::TileType::Obstacle || isStartTileType( t ) ||  isEndTileType( t ));
}


const std::array<SlidingTiles::TileType,4> END_TILES {SlidingTiles::TileType::EndTop, 
    SlidingTiles::TileType::EndBottom, SlidingTiles::TileType::EndLeft, 
    SlidingTiles::TileType::EndRight};

/**
 * @brief Returns if a random end TileType
 */
auto randomEndTileType() -> SlidingTiles::TileType {
    return END_TILES.at(random() % END_TILES.size());
}

auto isGameTileType(const SlidingTiles::TileType & t) -> bool {
    switch (t) {
        case SlidingTiles::TileType::Horizontal:
            return true;
        case SlidingTiles::TileType::Vertical:
            return true;
        case SlidingTiles::TileType::LeftTop:
            return true;
        case SlidingTiles::TileType::LeftBottom:
            return true;
        case SlidingTiles::TileType::TopRight:
            return true;
        case SlidingTiles::TileType::BottomRight:
            return true;
        default:
            return false;

    }
}

const std::array<SlidingTiles::TileType,7> GAME_TILES {
    SlidingTiles::TileType::Horizontal,
    SlidingTiles::TileType::Vertical, 
    SlidingTiles::TileType::LeftTop, 
    SlidingTiles::TileType::LeftBottom, 
    SlidingTiles::TileType::TopRight, 
    SlidingTiles::TileType::BottomRight, 
    SlidingTiles::TileType::Obstacle};

auto randomGameTileType() -> SlidingTiles::TileType {
    return GAME_TILES.at(random() % GAME_TILES.size());
}