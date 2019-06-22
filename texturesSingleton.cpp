#include "texturesSingleton.h"

SlidingTiles::TexturesSingleton::TexturesSingleton() {
    sf::Texture texture;

    // TODO(richi): Better to load the textures in one big blob
    texture.loadFromFile("assets/horizontal.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Horizontal] = texture;
    texture.loadFromFile("assets/vertical.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Vertical] = texture;

    texture.loadFromFile("assets/startbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartBottom] = texture;
    texture.loadFromFile("assets/starttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartTop] = texture;
    texture.loadFromFile("assets/startleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartLeft] = texture;
    texture.loadFromFile("assets/startright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::StartRight] = texture;

    texture.loadFromFile("assets/endtop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndTop] = texture;
    texture.loadFromFile("assets/endbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndBottom] = texture;
    texture.loadFromFile("assets/endleft.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndLeft] = texture;
    texture.loadFromFile("assets/endright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::EndRight] = texture;

    texture.loadFromFile("assets/lefttop.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftTop] = texture;
    texture.loadFromFile("assets/leftbottom.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::LeftBottom] = texture;
    texture.loadFromFile("assets/topright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::TopRight] = texture;
    texture.loadFromFile("assets/bottomright.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::BottomRight] = texture;
    texture.loadFromFile("assets/obstacle.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Obstacle] = texture;
    texture.loadFromFile("assets/empty.png"); //NOLINT (fuchsia-default-arguments)
    texturesMap[SlidingTiles::TileType::Empty] = texture;
};
