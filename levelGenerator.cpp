#include "puzzleSolver.h"
#include <iostream>

using namespace SlidingTiles;

auto main() -> int {
  PuzzleSolver puzzleSolver{};
  try {
    puzzleSolver.generateGames(10);
  } catch (zmq::error_t &e) {
    std::cout << e.what() << std::endl;
  }
}
