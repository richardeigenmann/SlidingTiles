#include "texturesSingleton.h"
#include "renderingSingleton.h"

SlidingTiles::TexturesSingleton::TexturesSingleton() {
    sf::Texture texture;

    // TODO(richi): Better to load the textures in one big blob
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "horizontal.png");
    texturesMap[SlidingTiles::TileType::Horizontal] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "vertical.png");
    texturesMap[SlidingTiles::TileType::Vertical] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startbottom.png");
    texturesMap[SlidingTiles::TileType::StartBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "starttop.png");
    texturesMap[SlidingTiles::TileType::StartTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startleft.png");
    texturesMap[SlidingTiles::TileType::StartLeft] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startright.png");
    texturesMap[SlidingTiles::TileType::StartRight] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endtop.png");
    texturesMap[SlidingTiles::TileType::EndTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endbottom.png");
    texturesMap[SlidingTiles::TileType::EndBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endleft.png");
    texturesMap[SlidingTiles::TileType::EndLeft] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endright.png");
    texturesMap[SlidingTiles::TileType::EndRight] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "lefttop.png");
    texturesMap[SlidingTiles::TileType::LeftTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "leftbottom.png");
    texturesMap[SlidingTiles::TileType::LeftBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "topright.png");
    texturesMap[SlidingTiles::TileType::TopRight] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "bottomright.png");
    texturesMap[SlidingTiles::TileType::BottomRight] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "obstacle.png");
    texturesMap[SlidingTiles::TileType::Obstacle] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "empty.png");
    texturesMap[SlidingTiles::TileType::Empty] = texture;
};
