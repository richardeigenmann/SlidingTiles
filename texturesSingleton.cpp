#include "texturesSingleton.h"
#include "executablePath.h"
#include "tileType.h"
#include <SFML/Graphics/Texture.hpp>

SlidingTiles::TexturesSingleton::TexturesSingleton() noexcept(false) {
    sf::Texture texture;

    // TODO(richi): Better to load the textures in one big blob
    auto assetDir = getAssetDir();
    texture.loadFromFile(assetDir + "horizontal.png");
    texturesMap[SlidingTiles::TileType::Horizontal] = texture;
    texture.loadFromFile(assetDir + "vertical.png");
    texturesMap[SlidingTiles::TileType::Vertical] = texture;

    texture.loadFromFile(assetDir + "startbottom.png");
    texturesMap[SlidingTiles::TileType::StartBottom] = texture;
    texture.loadFromFile(assetDir + "starttop.png");
    texturesMap[SlidingTiles::TileType::StartTop] = texture;
    texture.loadFromFile(assetDir + "startleft.png");
    texturesMap[SlidingTiles::TileType::StartLeft] = texture;
    texture.loadFromFile(assetDir + "startright.png");
    texturesMap[SlidingTiles::TileType::StartRight] = texture;

    texture.loadFromFile(assetDir + "endtop.png");
    texturesMap[SlidingTiles::TileType::EndTop] = texture;
    texture.loadFromFile(assetDir + "endbottom.png");
    texturesMap[SlidingTiles::TileType::EndBottom] = texture;
    texture.loadFromFile(assetDir + "endleft.png");
    texturesMap[SlidingTiles::TileType::EndLeft] = texture;
    texture.loadFromFile(assetDir + "endright.png");
    texturesMap[SlidingTiles::TileType::EndRight] = texture;

    texture.loadFromFile(assetDir + "lefttop.png");
    texturesMap[SlidingTiles::TileType::LeftTop] = texture;
    texture.loadFromFile(assetDir + "leftbottom.png");
    texturesMap[SlidingTiles::TileType::LeftBottom] = texture;
    texture.loadFromFile(assetDir + "topright.png");
    texturesMap[SlidingTiles::TileType::TopRight] = texture;
    texture.loadFromFile(assetDir + "bottomright.png");
    texturesMap[SlidingTiles::TileType::BottomRight] = texture;
    texture.loadFromFile(assetDir + "obstacle.png");
    texturesMap[SlidingTiles::TileType::Obstacle] = texture;
    texture.loadFromFile(assetDir + "empty.png");
    texturesMap[SlidingTiles::TileType::Empty] = texture;
};
