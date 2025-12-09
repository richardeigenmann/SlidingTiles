#include "tileType.h"
#include <array>
#include <random>

auto tileTypeToString(const SlidingTiles::TileType &t) -> std::string {
  switch (t) {
  case SlidingTiles::TileType::Empty:
    return "Empty";
  case SlidingTiles::TileType::Horizontal:
    return "Horizontal";
  case SlidingTiles::TileType::Vertical:
    return "Vertical";
  case SlidingTiles::TileType::StartTop:
    return "StartTop";
  case SlidingTiles::TileType::StartBottom:
    return "StartBottom";
  case SlidingTiles::TileType::StartLeft:
    return "StartLeft";
  case SlidingTiles::TileType::StartRight:
    return "StartRight";
  case SlidingTiles::TileType::EndTop:
    return "EndTop";
  case SlidingTiles::TileType::EndBottom:
    return "EndBottom";
  case SlidingTiles::TileType::EndRight:
    return "EndRight";
  case SlidingTiles::TileType::EndLeft:
    return "EndLeft";
  case SlidingTiles::TileType::LeftTop:
    return "LeftTop";
  case SlidingTiles::TileType::LeftBottom:
    return "LeftBottom";
  case SlidingTiles::TileType::TopRight:
    return "TopRight";
  case SlidingTiles::TileType::BottomRight:
    return "BottomRight";
  case SlidingTiles::TileType::Obstacle:
    return "Obstacle";
  default:
    return "Unknown Type";
  }
}

auto stringToTileType(const std::string &s) -> SlidingTiles::TileType {
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

auto tileTypeToWstringChar(const SlidingTiles::TileType &t) -> std::wstring {
  switch (t) {
  case SlidingTiles::TileType::Empty:
    return L" ";
  case SlidingTiles::TileType::Horizontal:
    return L"-";
  case SlidingTiles::TileType::Vertical:
    return L"|";
  case SlidingTiles::TileType::StartTop:
    return L"┴";
  case SlidingTiles::TileType::StartBottom:
    return L"┬";
  case SlidingTiles::TileType::StartLeft:
    return L"┤";
  case SlidingTiles::TileType::StartRight:
    return L"├";
  case SlidingTiles::TileType::EndTop:
    return L"┻";
  case SlidingTiles::TileType::EndBottom:
    return L"┳";
  case SlidingTiles::TileType::EndRight:
    return L"┣";
  case SlidingTiles::TileType::EndLeft:
    return L"┫";
  case SlidingTiles::TileType::LeftTop:
    return L"┘";
  case SlidingTiles::TileType::LeftBottom:
    return L"┐";
  case SlidingTiles::TileType::TopRight:
    return L"└";
  case SlidingTiles::TileType::BottomRight:
    return L"┌";
  case SlidingTiles::TileType::Obstacle:
    return L"o";
  default:
    return L"?";
  }
}

/**
 * @brief Returns if a TileType is a start tile
 */
auto isStartTileType(const SlidingTiles::TileType &t) -> bool {
  return t == SlidingTiles::TileType::StartTop ||
         t == SlidingTiles::TileType::StartBottom ||
         t == SlidingTiles::TileType::StartLeft ||
         t == SlidingTiles::TileType::StartRight;
}

const std::array<SlidingTiles::TileType, 4> START_TILES{
    SlidingTiles::TileType::StartTop, SlidingTiles::TileType::StartBottom,
    SlidingTiles::TileType::StartLeft, SlidingTiles::TileType::StartRight};

/**
 * @brief Returns if a random start TileType
 */
auto randomStartTileType() -> SlidingTiles::TileType {
  std::random_device rd{};
  std::mt19937 mtgen = std::mt19937{rd()};
  auto ud = std::uniform_int_distribution<>(0, START_TILES.size() - 1);
  return START_TILES.at(ud(mtgen));
  // return START_TILES.at(random() % START_TILES.size());
}

/**
 * @brief Returns if a TileType is an end tile
 */
auto isEndTileType(const SlidingTiles::TileType &t) -> bool {
  return t == SlidingTiles::TileType::EndTop ||
         t == SlidingTiles::TileType::EndBottom ||
         t == SlidingTiles::TileType::EndLeft ||
         t == SlidingTiles::TileType::EndRight;
}

/**
 * @brief Returns if a TileType is moveable
 */
auto isMoveableType(const SlidingTiles::TileType &t) -> bool {
  return !(t == SlidingTiles::TileType::Empty ||
           t == SlidingTiles::TileType::Obstacle || isStartTileType(t) ||
           isEndTileType(t));
}

const std::array<SlidingTiles::TileType, 4> END_TILES{
    SlidingTiles::TileType::EndTop, SlidingTiles::TileType::EndBottom,
    SlidingTiles::TileType::EndLeft, SlidingTiles::TileType::EndRight};

/**
 * @brief Returns if a random end TileType
 */
auto randomEndTileType() -> SlidingTiles::TileType {
  std::random_device rd{};
  std::mt19937 mtgen = std::mt19937{rd()};
  auto ud = std::uniform_int_distribution<>(0, END_TILES.size() - 1);
  return END_TILES.at(ud(mtgen));
  // return END_TILES.at(random() % END_TILES.size());
}

auto isGameTileType(const SlidingTiles::TileType &t) -> bool {
  return t == SlidingTiles::TileType::Horizontal ||
         t == SlidingTiles::TileType::Vertical ||
         t == SlidingTiles::TileType::LeftTop ||
         t == SlidingTiles::TileType::LeftBottom ||
         t == SlidingTiles::TileType::TopRight ||
         t == SlidingTiles::TileType::BottomRight;
}

const std::array<SlidingTiles::TileType, 7> GAME_TILES{
    SlidingTiles::TileType::Horizontal, SlidingTiles::TileType::Vertical,
    SlidingTiles::TileType::LeftTop,    SlidingTiles::TileType::LeftBottom,
    SlidingTiles::TileType::TopRight,   SlidingTiles::TileType::BottomRight,
    SlidingTiles::TileType::Obstacle};

auto randomGameTileType() -> SlidingTiles::TileType {
  std::random_device rd{};
  std::mt19937 mtgen = std::mt19937{rd()};
  auto ud = std::uniform_int_distribution<>(0, GAME_TILES.size() - 1);
  return GAME_TILES.at(ud(mtgen));
}