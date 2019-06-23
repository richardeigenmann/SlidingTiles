#include "game.h"
#include <experimental/filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "argv[0] reads: " << argv[0] << std::endl;
    std::string argv0 = argv[0];
    std::cout << "argv0 reads: " << argv0 << std::endl;
    std::experimental::filesystem::path p {argv0};
    std::cout << "path: " << p << std::endl;
    std::cout << "parent: " << p.parent_path() << std::endl;
    std::string assetDir = p.parent_path().string() + "/sliding-tiles-assets/";
    std::cout << "assetDir: " << assetDir << std::endl;
    SlidingTiles::RenderingSingleton::getInstance().setAssetDir(assetDir);
    SlidingTiles::Game game{};
    game.run();
}
