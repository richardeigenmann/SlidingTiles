#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"
#include "renderingSingleton.h"
#include "tileObserver.h"
#include "renderable.h"

namespace SlidingTiles {

    /**
     * @brief The view class for the tile that knows how to render itself
     */
    class TileView : public TileObserver, public Renderable {
    public:

        /**
         * @brief Constructs a new TileView with the appropriate screen coordinates
         */
        TileView(sf::Vector2i tileCoordinates) : tileCoordinates(tileCoordinates) {
            RenderingSingleton::getInstance().add(*this);
        };

        /**
         * @brief Destructor
         */
        ~TileView() {
            RenderingSingleton::getInstance().remove(*this);
        }

        /**
         * @brief knows how to render the tile
         */
        void render() override;

        /**
         * Tiles that are transitioning return OnTop priority whilst others
         * return Normal priorits
         * @return RenderPriority::OnTop for transitioning slides, 
         * RenderPriority::Normal for the other ones
         */
        Renderable::RenderPriority getRenderPriority() override;
        
        /**
         * @brief need to be called periodically with a delta time to
         * update the position etc.
         * @param dt The passing time since last call in seconds
         */
        void update(const float dt) override;

        /**
         * @brief starts a transition to the supplied new game coordinates
         * @return true if transition kicked off, false if not
         */
        void transition(const sf::Vector2i & newGameBoardPosition) override;

        /**
         * @brief settor for the tile type
         * @param newType the new type of the tile. Will figure out the correct texture from the TexturesSingleton
         */
        void setTileType(const TileType & newType) override {
            tileType = newType;
        };

        /**
         * @brief a bool to tell us if the tile is currently undergoing a transition
         */
        bool transitioning{false};

        /**
         * @brief settor for the tile coordinates in game coordinates
         */
        void setCoordinates(const sf::Vector2i & newGameBoardPosition) override {
            tileCoordinates = RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition);
        };

        /**
         * @brief gettor for the tile coordinates in screen coordinates
         * @return the coordinates
         */
        const sf::Vector2i & getCoordinates() {
            return tileCoordinates;
        };

        /**
         * @brief settor for the winner flag
         */
        void setWinner(const bool & status) override {
            winner = status;
        };

    private:
        /**
         * @brief A constant that gives the amount of time in seconds that the transition will last
         */
        static constexpr double TRANSITION_TIME{0.15}; // seconds

        /**
         * @brief a tracker to figure out how much of TRANSITION_TIME has passed
         */
        double timeSpentTransitioning{0};

        /**
         * The coordinates of the tile
         */
        sf::Vector2i tileCoordinates{0, 0};

        /**
         * The coordinates where to move the tile to if transitioning is true
         */
        sf::Vector2i transitionTileCoordiantes{0, 0};

        /**
         * @brief The color with which to tint the textures
         */
        sf::Color tileColor;

        /**
         * @brief a bool to tell us if the tile is part of the solution path or not
         */
        bool winner{false};

        /**
         * @brief the type of the tile
         */
        TileType tileType{TileType::Empty};
    };
} // namespace SlidingTiles
