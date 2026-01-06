#include "attitudeSoundPlayer.h"
#include "gameBoard.h"
#include "gameView.h"
#include "levelLabel.h"
#include "movesLabel.h"
#include "nextButton.h"
#include "parLabel.h"
#include "randomButton.h"
#include "renderable.h"
#include "renderingSingleton.h"
#include "restartButton.h"
#include "tileView.h"
#include "undoButton.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <utility>

SlidingTiles::GameView::GameView() {
  RenderingSingleton::getInstance().add(*this);

  randomSfmlButton = std::make_unique<RandomButton>();
  nextSfmlButton = std::make_unique<NextButton>();
  restartSfmlButton = std::make_unique<RestartButton>();
  undoButton = std::make_unique<UndoButton>();
  attitudeSoundPlayer = std::make_unique<AttitudeSoundPlayer>();
  levelLabel = std::make_unique<LevelLabel>();
  parLabel = std::make_unique<ParLabel>();
  movesLabel = std::make_unique<MovesLabel>();

  for (int y = 0; y < GameBoard::boardSize; ++y) {
    for (int x = 0; x < GameBoard::boardSize; ++x) {
      std::unique_ptr<TileView> tileView(new TileView(sf::Vector2i{x, y}));
      tileViews.push_back(std::move(tileView));
    }
  }
}

void SlidingTiles::GameView::render() {
  RenderingSingleton::getInstance().getRenderWindow()->clear(sf::Color::White);
}

auto SlidingTiles::GameView::getRenderPriority() const
    -> SlidingTiles::Renderable::RenderPriority {
  return SlidingTiles::Renderable::RenderPriority::Background;
}
