#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"
#include "renderingSingleton.h"

namespace SlidingTiles {
/**
 * @brief The view class for the tile that knows how to render itself
 */
class TileView {
    public:
        TileView(){};  // Don't want
        TileView( sf::Vector2i tileCoordinates )
            : tileCoordinates(tileCoordinates) {};
        void render();
        void update(const float dt);

        /**
        * @brief starts a transition to the supplied new pixel coordinates
        * @return true if transition kicked off, false if not
        */
        bool transition(sf::Vector2i newTileCoordinates);

        void setTexture(TileType newType) { setTexture(TexturesSingleton::getInstance().getTexturesMap()[newType]);};

        bool transitioning {false};
        void setCoordinates( sf::Vector2i newCoordinates ) { tileCoordinates = newCoordinates; };
        void setWinner(bool status) {
            winner = status;
        };

    private:
        static constexpr double TRANSITION_TIME {0.25}; // seconds
        double timeSpentTransitioning {0};

        /**
        * The coordinates of the tile
        */
        sf::Vector2i tileCoordinates {0, 0};

        /**
        * The coordinates where to move the tile to if transitioning is true
        */
        sf::Vector2i transitionTileCoordiantes {0, 0};

        sf::Color tileColor;

        sf::Texture tileTexture;
        void setTexture(sf::Texture newTexture) { tileTexture = newTexture; };

        bool winner {false};
};


} // namespace SlidingTiles