#include "puzzleSolver.h"
#include <iostream>

using namespace SlidingTiles;

auto main() -> int {
  PuzzleSolver puzzleSolver{};
  try {
    puzzleSolver.generateGames(10);
  } catch (zmq::error_t &e) {
    std::cout << e.what() << '\n';
  } catch (const std::out_of_range &e) {
    std::cerr << "Out of Range Error: " << e.what() << '\n';
    return 1;
  } catch (const std::exception &e) {
    std::cerr << "Standard Exception: " << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown error occurred!" << '\n';
    return 1;
  }
  return 0;
}
