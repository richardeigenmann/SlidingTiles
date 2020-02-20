#include "gameView.h"
#include <gmock/gmock.h>
#include "game.h"

using namespace SlidingTiles;

TEST(GameView, ObjectCreation) {
    SlidingTiles::GameView gameView{};
}

TEST(GameView, renderMethod) {
    std::wstring game{L"          -   ├┐"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    SlidingTiles::GameView gameView{};
    gameView.setGameBoard(&gameBoard);

    gameView.render();
}
