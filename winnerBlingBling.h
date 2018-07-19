#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "json.hpp"
#include "randomSoundPlayer.h"
#include "renderable.h"
#include "gameState.h"
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "renderingSingleton.h"
#include "zmqSingleton.h"
#include "zmqSubscriber.h"


namespace SlidingTiles {

    /**
     * @brief The class that will gratify the winner of the game
     */
    class WinnerBlingBling : public Renderable, public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for winner bling bling
         */
        WinnerBlingBling();

        /**
         * @brief Destructor for winner bling bling
         */
        ~WinnerBlingBling();

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
         * @brief update callback
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

        /**
         * Call this method to have the button rendered
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
         * @brief call this to start the bling bling
         * @param time The amount of time it will last
         * @param moves the number of moves it took to solve
         * @param par the par number of moves to solve
         */
        void startBlingBling(const float & time, std::size_t moves, std::size_t par);

        /**
         * @brief call this to end the bling bling
         */
        void endBlingBling();

        /**
         * @brief The texture of the button
         */
        sf::Texture texture;

        /**
         * @brief The sprite of the button
         */
        sf::Sprite sprite;

        /**
         * an object with winner sounds to be played randomly when a game is won 
         */
        RandomSoundPlayer winnerSounds;

        /**
         * local variable to remember the state of the game
         */
        GameState gameState{GameState::Initializing};
    };
}
