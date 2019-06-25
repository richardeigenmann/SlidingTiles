#include "game.h"
#include <iostream>

int main(int argc, char *argv[]) { // NOLINT (misc-unused-parameters)
    SlidingTiles::RenderingSingleton::getInstance().setAssetDir(std::string(argv[0]));
    SlidingTiles::Game game{};
    game.run();
}
