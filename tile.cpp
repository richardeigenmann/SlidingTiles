#include "direction.h"
#include "tile.h"
#include "tileType.h"
#include <SFML/System/Vector2.hpp>
#include <string>

namespace SlidingTiles {

/**
 * Sets the type of the tile.
 * passes on the request to the tileView so that it can adjust the texture
 */
void Tile::setTileType(const TileType &newType) {
  tileType = newType;
  setMoveable(newType);
};

/**
 * Sets the type of the tile based on a character code
 */
void Tile::setTileType(const std::string &c) {
  if (c == "-") {
    setTileType(TileType::Horizontal);
  } else if (c == "|") {
    setTileType(TileType::Vertical);

  } else if (c == "└") {
    setTileType(TileType::TopRight);
  } else if (c == "┘") {
    setTileType(TileType::LeftTop);
  } else if (c == "┐") {
    setTileType(TileType::LeftBottom);
  } else if (c == "┌") {
    setTileType(TileType::BottomRight);

  } else if (c == "├") {
    setTileType(TileType::StartRight);
  } else if (c == "┬") {
    setTileType(TileType::StartBottom);
  } else if (c == "┴") {
    setTileType(TileType::StartTop);
  } else if (c == "┤") {
    setTileType(TileType::StartLeft);

  } else if (c == "┻") {
    setTileType(TileType::EndTop);
  } else if (c == "┣") {
    setTileType(TileType::EndRight);
  } else if (c == "┫") {
    setTileType(TileType::EndLeft);
  } else if (c == "┳") {
    setTileType(TileType::EndBottom);
  } else if (c == "o") {
    setTileType(TileType::Obstacle);
  } else {
    setTileType(TileType::Empty);
  }
}

/**
 * Sets the type of the tile based on a character code
 */
void Tile::setTileType(const std::wstring &c) {
  if (c == L"-") {
    setTileType(TileType::Horizontal);
  } else if (c == L"|") {
    setTileType(TileType::Vertical);

  } else if (c == L"└") {
    setTileType(TileType::TopRight);
  } else if (c == L"┘") {
    setTileType(TileType::LeftTop);
  } else if (c == L"┐") {
    setTileType(TileType::LeftBottom);
  } else if (c == L"┌") {
    setTileType(TileType::BottomRight);

  } else if (c == L"├") {
    setTileType(TileType::StartRight);
  } else if (c == L"┬") {
    setTileType(TileType::StartBottom);
  } else if (c == L"┴") {
    setTileType(TileType::StartTop);
  } else if (c == L"┤") {
    setTileType(TileType::StartLeft);

  } else if (c == L"┻") {
    setTileType(TileType::EndTop);
  } else if (c == L"┣") {
    setTileType(TileType::EndRight);
  } else if (c == L"┫") {
    setTileType(TileType::EndLeft);
  } else if (c == L"┳") {
    setTileType(TileType::EndBottom);
  } else if (c == L"o") {
    setTileType(TileType::Obstacle);
  } else {
    setTileType(TileType::Empty);
  }
}

namespace {
  auto isStaticTile(const TileType type) -> bool {
    switch (type) {
      case TileType::Empty:
      case TileType::Obstacle:
      case TileType::StartBottom:
      case TileType::StartTop:
      case TileType::StartLeft:
      case TileType::StartRight:
      case TileType::EndBottom:
      case TileType::EndTop:
      case TileType::EndLeft:
      case TileType::EndRight:
        return true;
      default:
        return false;
    }
  }
} // anonymous namespace

void Tile::setMoveable(const TileType &newType) {
  isMoveable = isMoveable = !isStaticTile(newType);
};

void Tile::transition(const sf::Vector2i &newGameBoardPosition) {
  myPosition = newGameBoardPosition;
}

/**
 * Returns the direction coming out of the supplied tile and incoming direction.
 */
auto Tile::outputDirection(const Direction &incomingDirection) const -> Direction {
  switch (tileType) {
    // Entry points: They ignore incoming direction
    case TileType::StartRight:  return Direction::GoRight;
    case TileType::StartLeft:   return Direction::GoLeft;
    case TileType::StartTop:    return Direction::GoUp;
    case TileType::StartBottom: return Direction::GoDown;

      // Straight paths: Pass through if aligned
    case TileType::Horizontal:
      if (incomingDirection == Direction::GoRight || incomingDirection == Direction::GoLeft) {
        return incomingDirection;
      }
      break;

    case TileType::Vertical:
      if (incomingDirection == Direction::GoUp || incomingDirection == Direction::GoDown) {
        return incomingDirection;
      }
      break;

      // Corner paths: Change direction
    case TileType::LeftBottom:
      if (incomingDirection == Direction::GoRight) { return Direction::GoDown; }
      if (incomingDirection == Direction::GoUp)    { return Direction::GoLeft; }
      break;

    case TileType::LeftTop:
      if (incomingDirection == Direction::GoDown)  { return Direction::GoLeft; }
      if (incomingDirection == Direction::GoRight) { return Direction::GoUp; }
      break;

    case TileType::TopRight:
      if (incomingDirection == Direction::GoDown)  { return Direction::GoRight; }
      if (incomingDirection == Direction::GoLeft)  { return Direction::GoUp; }
      break;

    case TileType::BottomRight:
      if (incomingDirection == Direction::GoLeft)  { return Direction::GoDown; }
      if (incomingDirection == Direction::GoUp)    { return Direction::GoRight; }
      break;

    default:
      break;
  }

  return Direction::Unknown;
}

void Tile::setWinner(const bool &status) { winner = status; }

} // namespace SlidingTiles
