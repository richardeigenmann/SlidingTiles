#include "tile.h"

namespace SlidingTiles {

    /**
     * Sets the type of the tile
     * passes on the request to the tileView so that it can adjust the texture
     */
    void Tile::setTileType(const TileType & newType) {
        tileType = newType;
        setMoveable(newType);
    };

    /**
     * Sets the type of the tile based on a character code
     */
    void Tile::setTileType(const std::string & c) {
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
    void Tile::setTileType(const std::wstring & c) {
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

    void Tile::setMoveable(const TileType & newType) {
        isMoveable = ! (newType == TileType::Empty
                || newType == TileType::StartBottom
                || newType == TileType::StartTop
                || newType == TileType::StartLeft
                || newType == TileType::StartRight
                || newType == TileType::EndBottom
                || newType == TileType::EndTop
                || newType == TileType::EndLeft
                || newType == TileType::EndRight
                || newType == TileType::Obstacle);
    };

    void Tile::transition(const sf::Vector2i & newGameBoardPosition) {
        myPosition = newGameBoardPosition;
    }

    /**
     * Returns the direction coming out of the supplied tile and incoming direction.
     */
    Direction Tile::outputDirection(const Direction & incomingDirection) {
        if (tileType == TileType::StartRight) {
            return Direction::GoRight;
        }
        if (tileType == TileType::StartLeft) {
            return Direction::GoLeft;
        }
        if (tileType == TileType::StartTop) {
            return Direction::GoUp;
        }
        if (tileType == TileType::StartBottom) {
            return Direction::GoDown;
        }
        if (tileType == TileType::Horizontal
                && (incomingDirection == Direction::GoRight || incomingDirection == Direction::GoLeft)) {
            return incomingDirection;
        }
        if (tileType == TileType::Vertical
                && (incomingDirection == Direction::GoUp || incomingDirection == Direction::GoDown)) {
            return incomingDirection;
        }
        if (tileType == TileType::LeftBottom && incomingDirection == Direction::GoRight) {
            return Direction::GoDown;
        }
        if (tileType == TileType::LeftBottom && incomingDirection == Direction::GoUp) {
            return Direction::GoLeft;
        }
        if (tileType == TileType::LeftTop && incomingDirection == Direction::GoDown) {
            return Direction::GoLeft;
        }
        if (tileType == TileType::LeftTop && incomingDirection == Direction::GoRight) {
            return Direction::GoUp;
        }
        if (tileType == TileType::TopRight && incomingDirection == Direction::GoDown) {
            return Direction::GoRight;
        }
        if (tileType == TileType::TopRight && incomingDirection == Direction::GoLeft) {
            return Direction::GoUp;
        }
        if (tileType == TileType::BottomRight && incomingDirection == Direction::GoLeft) {
            return Direction::GoDown;
        }
        if (tileType == TileType::BottomRight && incomingDirection == Direction::GoUp) {
            return Direction::GoRight;
        }

        return Direction::Unknown;
    }

    void Tile::setWinner(const bool & status) {
        winner = status;
    }

} // namespace SlidingTiles
