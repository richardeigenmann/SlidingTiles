#include "texturesSingleton.h"

SlidingTiles::TexturesSingleton::TexturesSingleton() {
    sf::Texture texture;

    // TODO(richi): Better to load the textures in one big blob
    texture.loadFromFile("sliding-tiles-assets/horizontal.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Horizontal] = texture;
    texture.loadFromFile("sliding-tiles-assets/vertical.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Vertical] = texture;

    texture.loadFromFile("sliding-tiles-assets/startbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartBottom] = texture;
    texture.loadFromFile("sliding-tiles-assets/starttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartTop] = texture;
    texture.loadFromFile("sliding-tiles-assets/startleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartLeft] = texture;
    texture.loadFromFile("sliding-tiles-assets/startright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartRight] = texture;

    texture.loadFromFile("sliding-tiles-assets/endtop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndTop] = texture;
    texture.loadFromFile("sliding-tiles-assets/endbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndBottom] = texture;
    texture.loadFromFile("sliding-tiles-assets/endleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndLeft] = texture;
    texture.loadFromFile("sliding-tiles-assets/endright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndRight] = texture;

    texture.loadFromFile("sliding-tiles-assets/lefttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftTop] = texture;
    texture.loadFromFile("sliding-tiles-assets/leftbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftBottom] = texture;
    texture.loadFromFile("sliding-tiles-assets/topright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::TopRight] = texture;
    texture.loadFromFile("sliding-tiles-assets/bottomright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::BottomRight] = texture;
    texture.loadFromFile("sliding-tiles-assets/obstacle.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Obstacle] = texture;
    texture.loadFromFile("sliding-tiles-assets/empty.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Empty] = texture;
};
