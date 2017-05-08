#include "tileView.h"
#include "renderable.h"
#include "json.hpp"

using json = nlohmann::json;

namespace SlidingTiles {

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
        if (winner)
            sprite.setColor(sf::Color{0, 255, 0});
        if (isStartTileType(tileType))
            sprite.setColor(sf::Color{96, 206, 237});
        else if (isEndTileType(tileType))
            sprite.setColor(sf::Color{255, 0, 0});

        RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
    }

    void TileView::update(const float dt) {
        //std::cout << "tv update\n";
        if (transitioning) {
            timeSpentTransitioning += dt;
            if (timeSpentTransitioning > TRANSITION_TIME) {
                transitioning = false;
                tileScreenCoordinates = transitionTileCoordiantes;
                //renderPriority = RenderPriority::Normal;
            }
        }

        zmq::message_t reply;
        if (socket.recv(&reply, ZMQ_NOBLOCK)) {
            std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
            //std::cout << "tileView received: " << message << std::endl;
            auto j = json::parse(message);
            std::string state = j["state"].get<std::string>();
            if (state == PublishingSingleton::SLIDE_TILE) {
                int startPositionX = j["startPosition"]["x"];
                int startPositionY = j["startPosition"]["y"];
                int newPositionX = j["newPosition"]["x"];
                int newPositionY = j["newPosition"]["y"];
                if (tileGameCoordinates.x == startPositionX && tileGameCoordinates.y == startPositionY) {
                    std::cout << "I am a TileView that needs to transition: I am x: " << tileGameCoordinates.x << " y: " << tileGameCoordinates.y << " and the message is for x: " << startPositionX << " y: " << startPositionY << "\n";
                    //transition(sf::Vector2i{newPositionX, newPositionY});
                } else if (tileGameCoordinates.x == newPositionX && tileGameCoordinates.y == newPositionX) {
                    std::cout << "I am a TileView that needs to setPosition: I am x: " << tileGameCoordinates.x << " y: " << tileGameCoordinates.y << " and the message is for x: " << startPositionX << " y: " << startPositionY << "\n";
                }
            } else if (state == PublishingSingleton::SET_TILE) {
                int x = j["position"]["x"];
                int y = j["position"]["y"];
                std::string tileTypeString = j["tileType"].get<std::string>();
                TileType tileType = stringToTileType(tileTypeString);
                if (tileGameCoordinates.x == x && tileGameCoordinates.y == y) {
                    std::cout << "I am a TileView that needs to setPosition and setTileType. I am x: " << tileGameCoordinates.x << " y: " << tileGameCoordinates.y << " and the message is for x: " << x << " y: " << y << " and tile type: " << tileTypeToString(tileType) << "\n";
                }
            }
        }
    }

    void TileView::transition(const sf::Vector2i & newGameBoardPosition) {
        std::cout << "i am doing transition. I am x: " << tileGameCoordinates.x << " y: " << tileGameCoordinates.y << "\n";
        tileGameCoordinates = newGameBoardPosition;
        transitionTileCoordiantes = RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition);
        timeSpentTransitioning = 0;
        //renderPriority = RenderPriority::OnTop;
        transitioning = true;
    }

    Renderable::RenderPriority TileView::getRenderPriority() {
        if (transitioning) {
            return Renderable::RenderPriority::OnTop;
        } else {
            return Renderable::RenderPriority::Normal;
        }
    }

}
