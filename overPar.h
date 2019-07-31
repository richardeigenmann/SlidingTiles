#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "randomSoundPlayer.h"
#include "renderable.h"
#include "gameState.h"
#include "updatingSingleton.h"
#include "renderingSingleton.h"
#include "zmqSingleton.h"
#include "zmqSubscriber.h"


namespace SlidingTiles {

    /**
     * @brief The class that will show the user she is over par
     */
    class OverPar : public Renderable, public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for over par notice
         */
        explicit OverPar();

        /**
         * @brief Destructor for over par notice
         */
        ~OverPar();

        /**
         * @brief Load method that takes the filenames in the JSON array and loads
         * the corresponding files into the sounds vector.
         * @param jsonArray The JSON array with File entries representing the filenames
         */
        void loadSounds(const json & jsonArray);

        /**
         * @brief set the position of the button
         */
        void setPosition(float x, float y);


        /**
         * @brief update callback for the update loop
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

        /**
         * Call this method to have the object rendered
         */
        void render() override;

        /**
         * @brief returns the sprite (for testing). I can't figure out how to do the FRIENDS_TEST
         */
        sf::Sprite & getSprite() {
            return sprite;
        }

    private:
        /**
         * @brief call this to show the over par class
         * @param moves the number of moves it took to solve
         * @param par the par number of moves to solve
         */
        void startOverPar();

        /**
         * @brief call this to start the new game
         */
        void newGame(const int par);

        /**
         * @brief call this to end the over par 
         */
        void endOverPar();

        /**
         * @brief The texture of the renderable
         */
        sf::Texture texture;

        /**
         * @brief The sprite of the renderable
         */
        sf::Sprite sprite;

        /**
         * an object with winner sounds to be played randomly when a game is won 
         */
        RandomSoundPlayer overParSounds;

        /**
         * local variable to remember the state of the game
         */
        GameState gameState{GameState::Initializing};

        /**
         * local variable to keep track of the moves played
         */
        int moves {0};

        /**
         * local variable to keep track of the par level of the game
         */
        int par {0};
    };
}
