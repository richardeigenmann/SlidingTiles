#include "tileView.h"
#include "renderable.h"
#include "json.hpp"

using json = nlohmann::json;

namespace SlidingTiles {
    int TileView::count = 0;

    void TileView::render() {
        sf::Vector2i renderPosition = tileScreenCoordinates;
        if (transitioning) {
            int deltaX = (transitionTileCoordiantes.x - tileScreenCoordinates.x) * timeSpentTransitioning / TRANSITION_TIME;
            int deltaY = (transitionTileCoordiantes.y - tileScreenCoordinates.y) * timeSpentTransitioning / TRANSITION_TIME;
            renderPosition.x += deltaX;
            renderPosition.y += deltaY;
        }

        sf::Sprite sprite;
        sprite.setTexture(TexturesSingleton::getInstance().getTexture(tileType));
        sprite.setPosition(renderPosition.x, renderPosition.y);
        if (winner) {
            sprite.setColor(sf::Color{0, 255, 0});
        }
        if (isStartTileType(tileType)) {
            sprite.setColor(sf::Color{96, 206, 237});
        } else {
            if (isEndTileType(tileType)) {
                sprite.setColor(sf::Color{255, 0, 0});
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
        std::string state = jsonMessage["state"].get<std::string>();
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
            std::string tileTypeString = jsonMessage["tileType"].get<std::string>();
            //TileType tileType = stringToTileType(tileTypeString);
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

    Renderable::RenderPriority TileView::getRenderPriority() const {
        if (transitioning) {
            return Renderable::RenderPriority::OnTop;
        }
        return Renderable::RenderPriority::Normal;
    }

}
