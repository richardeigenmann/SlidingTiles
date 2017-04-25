#include "gameView.h"
#include "renderingSingleton.h"

namespace SlidingTiles {

    GameView::GameView() {
        RenderingSingleton::getInstance().add(*this);
        renderPriority = Renderable::RenderPriority::Background;
    }

    void GameView::render() {
        RenderingSingleton::getInstance().getRenderWindow()->clear(sf::Color::White);
    }
}
