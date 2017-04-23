#include "tileView.h"

namespace SlidingTiles {

    void TileView::render() {
        sf::Vector2i renderPosition = tileCoordinates;
        if (transitioning) {
            int deltaX = (transitionTileCoordiantes.x - tileCoordinates.x) * timeSpentTransitioning / TRANSITION_TIME;
            int deltaY = (transitionTileCoordiantes.y - tileCoordinates.y) * timeSpentTransitioning / TRANSITION_TIME;
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
        if (transitioning) {
            timeSpentTransitioning += dt;
            if (timeSpentTransitioning > TRANSITION_TIME) {
                transitioning = false;
                tileCoordinates = transitionTileCoordiantes;
                renderPriority = RenderPriority::Normal;
            }
        }
    }

    void TileView::transition(const sf::Vector2i & newGameBoardPosition) {
        transitionTileCoordiantes = RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition);
        timeSpentTransitioning = 0;
        renderPriority = RenderPriority::OnTop;
        transitioning = true;
    }

}
