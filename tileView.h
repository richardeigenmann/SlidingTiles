#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"
#include "renderingSingleton.h"
#include "renderable.h"
#include "zmq.hpp"
#include "zmqSingleton.h"
#include <iostream>
#include "updatingSingleton.h"
#include "zmqSubscriber.h"

namespace SlidingTiles {

    /**
     * @brief The view class for the tile that knows how to render itself
     */
    class TileView : public Renderable, public Updateable, public ZmqSubscriber {
    public:

        /**
         * @brief Constructs a new TileView with the appropriate screen coordinates
         */
        TileView(sf::Vector2i tileCoordinates) : tileGameCoordinates(tileCoordinates) {
            RenderingSingleton::getInstance().add(*this);
            UpdatingSingleton::getInstance().add(*this);
            id = count;
            ++count;
        };

        /**
         * @brief Destructor
         */
        ~TileView() {
            RenderingSingleton::getInstance().remove(*this);
            UpdatingSingleton::getInstance().remove(*this);
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
        Renderable::RenderPriority getRenderPriority() const override;

        /**
         * @brief need to be called periodically with a delta time to
         * update the position etc.
         * @param dt The passing time since last call in seconds
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

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
         * The coordinates of the tile in game coordinates
         */
        sf::Vector2i tileGameCoordinates{0, 0};

        /**
         * The coordinates of the tile in screen coordinates
         */
        sf::Vector2i tileScreenCoordinates{0, 0};

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
         * @brief a bool to tell us if the tile is currently undergoing a transition
         */
        bool transitioning{false};

        /**
         * @brief the type of the tile
         */
        TileType tileType{TileType::Empty};

        /**
         * @brief settor for the winner flag
         */
        void setWinner(const bool & status) {
            winner = status;
        };

        /**
         * @brief settor for the tile coordinates in game coordinates
         */
        void setCoordinates(const sf::Vector2i & newGameBoardPosition) {
            tileGameCoordinates = newGameBoardPosition;
            tileScreenCoordinates = RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition);
        };

        /**
         * @brief gettor for the tile coordinates in screen coordinates
         * @return the coordinates
         */
        const sf::Vector2i & getCoordinates() {
            return tileScreenCoordinates;
        };

        /**
         * @brief starts a transition to the supplied new game coordinates
         * @return true if transition kicked off, false if not
         */
        void transition(const sf::Vector2i & newGameBoardPosition);

        /**
         * @brief settor for the tile type
         * @param newType the new type of the tile. Will figure out the correct texture from the TexturesSingleton
         */
        void setTileType(const TileType & newType) {
            tileType = newType;
        };

        /**
         * @brief prints debug information about the tileView
         */
        void debug() {
            std::cout << "TileView id:" << id << " game: [" << tileGameCoordinates.x << "][" << tileGameCoordinates.y << "]" << std::endl;
        }

        /**
         * @brief counter
         */
        static int count;

        /**
         * @brief My id
         */
        int id;
    };
} // namespace SlidingTiles
