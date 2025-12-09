#include "game.h"
#include <exception>
#include <iostream>

auto main() -> int {
  try {
    SlidingTiles::Game game{};
    game.run();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "An exception occurred";
  }
}
