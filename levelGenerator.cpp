#include "puzzleSolver.h"
#include <chrono>

using namespace SlidingTiles;

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    PuzzleSolver puzzleSolver{};
    puzzleSolver.generateGames(10);
}
