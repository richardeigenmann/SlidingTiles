#include "texturesSingleton.h"
#include "renderingSingleton.h"

SlidingTiles::TexturesSingleton::TexturesSingleton() {
    sf::Texture texture;

    // TODO(richi): Better to load the textures in one big blob
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "horizontal.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Horizontal] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "vertical.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Vertical] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "starttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartLeft] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "startright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartRight] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endtop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndLeft] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "endright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndRight] = texture;

    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "lefttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftTop] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "leftbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftBottom] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "topright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::TopRight] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "bottomright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::BottomRight] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "obstacle.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Obstacle] = texture;
    texture.loadFromFile(RenderingSingleton::getInstance().getAssetDir() + "empty.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Empty] = texture;
};
