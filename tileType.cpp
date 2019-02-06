#include "tileType.h"

std::string tileTypeToString(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            return "Empty";
        case TileType::Horizontal:
            return "Horizontal";
        case TileType::Vertical:
            return "Vertical";
        case TileType::StartTop:
            return "StartTop";
        case TileType::StartBottom:
            return "StartBottom";
        case TileType::StartLeft:
            return "StartLeft";
        case TileType::StartRight:
            return "StartRight";
        case TileType::EndTop:
            return "EndTop";
        case TileType::EndBottom:
            return "EndBottom";
        case TileType::EndRight:
            return "EndRight";
        case TileType::EndLeft:
            return "EndLeft";
        case TileType::LeftTop:
            return "LeftTop";
        case TileType::LeftBottom:
            return "LeftBottom";
        case TileType::TopRight:
            return "TopRight";
        case TileType::BottomRight:
            return "BottomRight";
        case TileType::Obstacle:
            return "Obstacle";
        default:
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

std::string tileTypeToChar(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            return " ";
        case TileType::Horizontal:
            return "-";
        case TileType::Vertical:
            return "|";
        case TileType::StartTop:
            return "┴";
        case TileType::StartBottom:
            return "┬";
        case TileType::StartLeft:
            return "┤";
        case TileType::StartRight:
            return "├";
        case TileType::EndTop:
            return "┻";
        case TileType::EndBottom:
            return "┳";
        case TileType::EndRight:
            return "┣";
        case TileType::EndLeft:
            return "┫";
        case TileType::LeftTop:
            return "┘";
        case TileType::LeftBottom:
            return "┐";
        case TileType::TopRight:
            return "└";
        case TileType::BottomRight:
            return "┌";
        case TileType::Obstacle:
            return "o";
        default:
            return "?";
    }
}

std::wstring tileTypeToWstringChar(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            return L" ";
        case TileType::Horizontal:
            return L"-";
        case TileType::Vertical:
            return L"|";
        case TileType::StartTop:
            return L"┴";
        case TileType::StartBottom:
            return L"┬";
        case TileType::StartLeft:
            return L"┤";
        case TileType::StartRight:
            return L"├";
        case TileType::EndTop:
            return L"┻";
        case TileType::EndBottom:
            return L"┳";
        case TileType::EndRight:
            return L"┣";
        case TileType::EndLeft:
            return L"┫";
        case TileType::LeftTop:
            return L"┘";
        case TileType::LeftBottom:
            return L"┐";
        case TileType::TopRight:
            return L"└";
        case TileType::BottomRight:
            return L"┌";
        case TileType::Obstacle:
            return L"o";
        default:
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

/**
 * @brief Returns if a random start TileType
 */
TileType randomStartTileType() {
    TileType startTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: startTileType = TileType::StartTop;
            break;
        case 1: startTileType = TileType::StartBottom;
            break;
        case 2: startTileType = TileType::StartLeft;
            break;
        case 3: startTileType = TileType::StartRight;
            break;
    }
    return startTileType;
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


/**
 * @brief Returns if a random end TileType
 */
TileType randomEndTileType() {
    TileType endTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: endTileType = TileType::EndTop;
            break;
        case 1: endTileType = TileType::EndBottom;
            break;
        case 2: endTileType = TileType::EndLeft;
            break;
        case 3: endTileType = TileType::EndRight;
            break;
    }
    return endTileType;
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

TileType randomGameTileType() {
    TileType gameTileType{TileType::Empty};
    switch (rand() % 7) {
        case 0: gameTileType = TileType::Horizontal;
            break;
        case 1: gameTileType = TileType::Vertical;
            break;
        case 2: gameTileType = TileType::LeftTop;
            break;
        case 3: gameTileType = TileType::LeftBottom;
            break;
        case 4: gameTileType = TileType::TopRight;
            break;
        case 5: gameTileType = TileType::BottomRight;
            break;
        case 6: gameTileType = TileType::Obstacle;
            break;
    }

    return gameTileType;
}