#include "gameView.h"
#include "renderingSingleton.h"

namespace SlidingTiles {

    GameView::GameView() {
        RenderingSingleton::getInstance().add(*this);

        for (int y = 0; y < GameBoard::boardSize; ++y) {
            for (int x = 0; x < GameBoard::boardSize; ++x) {
                std::unique_ptr<TileView> tileView(new TileView(sf::Vector2i{x, y}));
                tileViews.push_back(std::move(tileView));
            }
        }
    }

    void GameView::render() {
        RenderingSingleton::getInstance().getRenderWindow()->clear(sf::Color::White);
    }

    Renderable::RenderPriority GameView::getRenderPriority() const {
        return Renderable::RenderPriority::Background;
    }
}
