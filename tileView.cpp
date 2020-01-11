#include "json.hpp"
#include "renderable.h"
#include "tileView.h"

using json = nlohmann::json;

namespace SlidingTiles {
    int TileView::count = 0;

    const sf::Color WINNER_COLOR {sf::Color{0, 255, 0, 255}}; // NOLINT (cert-err58-cpp)
    const sf::Color START_COLOR {sf::Color{96, 206, 237, 255}}; // NOLINT (cert-err58-cpp)
    const sf::Color END_COLOR {sf::Color{255, 0, 0, 255}}; // NOLINT (cert-err58-cpp)


    void TileView::render() {
        sf::Vector2i renderPosition = tileScreenCoordinates;
        if (transitioning) {
            int deltaX = static_cast<int>((transitionTileCoordiantes.x - tileScreenCoordinates.x) * timeSpentTransitioning / TRANSITION_TIME);
            int deltaY = static_cast<int>((transitionTileCoordiantes.y - tileScreenCoordinates.y) * timeSpentTransitioning / TRANSITION_TIME);
            renderPosition.x += deltaX;
            renderPosition.y += deltaY;
        }

        sf::Sprite sprite;
        sprite.setTexture(TexturesSingleton::getInstance().getTexture(tileType));
        sprite.setPosition(renderPosition.x, renderPosition.y);
        if (winner) {
            sprite.setColor(WINNER_COLOR);
        }

        if (isStartTileType(tileType)) {
            sprite.setColor(START_COLOR);
        } else {
            if (isEndTileType(tileType)) {
                sprite.setColor(END_COLOR);
            }
        }

        RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
    }

    void TileView::update(const float dt) {
        if (transitioning) {
            timeSpentTransitioning += dt;
            if (timeSpentTransitioning > TRANSITION_TIME) {
                transitioning = false;
                tileScreenCoordinates = transitionTileCoordiantes;
            }
        }

        auto msg = getZmqMessage();
        if (msg) {
            handleMessage(msg.value());
        }
    }

    void TileView::handleMessage(const json & jsonMessage) {
        auto state = jsonMessage["state"].get<std::string>();
        if (state == ZmqSingleton::SLIDE_TILE) {
            int startPositionX = jsonMessage["startPosition"]["x"];
            int startPositionY = jsonMessage["startPosition"]["y"];
            int newPositionX = jsonMessage["newPosition"]["x"];
            int newPositionY = jsonMessage["newPosition"]["y"];
            if (tileGameCoordinates.x == startPositionX && tileGameCoordinates.y == startPositionY) {
                std::cout << "I am TileView " << id << " and am moving from "
                        << tileGameCoordinates.x << "x" << tileGameCoordinates.y
                        << " to " << newPositionX << "x" << newPositionY << std::endl;
                transition(sf::Vector2i{newPositionX, newPositionY});
            } else if (tileGameCoordinates.x == newPositionX && tileGameCoordinates.y == newPositionY) {
                std::cout << "I am TileView " << id << " nd am setting my coordinates from "
                        << tileGameCoordinates.x << "x" << tileGameCoordinates.y
                        << " to " << startPositionX << "x" << startPositionY << std::endl;
                setCoordinates(sf::Vector2i{startPositionX, startPositionY});
            }
        } else if (state == ZmqSingleton::SET_TILE) {
            int x = jsonMessage["position"]["x"];
            int y = jsonMessage["position"]["y"];
            auto tileTypeString = jsonMessage["tileType"].get<std::string>();
            if (tileGameCoordinates.x == x && tileGameCoordinates.y == y) {
                setCoordinates(sf::Vector2i{x, y});
                setTileType(stringToTileType(tileTypeString));
                setWinner(false);
            }
        } else if (state == ZmqSingleton::GAME_WON) {
            auto solutionTiles = jsonMessage["solutionTiles"];
            for (const auto & solutionTile : solutionTiles) {
                size_t x = solutionTile[0];
                size_t y = solutionTile[1];
                if (tileGameCoordinates.x == x && tileGameCoordinates.y == y) {
                    setWinner(true);
                }
            }
        } else if (state == ZmqSingleton::DEBUG) {
            debug();

        }
    }


    void TileView::transition(const sf::Vector2i & newGameBoardPosition) {
        tileGameCoordinates = newGameBoardPosition;
        transitionTileCoordiantes = RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition);
        timeSpentTransitioning = 0;
        transitioning = true;
    }

    auto TileView::getRenderPriority() const -> Renderable::RenderPriority {
        if (transitioning) {
            return Renderable::RenderPriority::OnTop;
        }
        return Renderable::RenderPriority::Normal;
    }

} // namespace SlidingTiles
