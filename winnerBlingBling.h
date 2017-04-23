#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "json.hpp"
#include "randomSoundPlayer.h"

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class WinnerBlingBling {
    public:
        /**
         * @brief Constructor for winner bling bling
         */
        WinnerBlingBling();

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
         * @brief call this to start the bling bling
         * @param time The amount of time it will last
         * @param moves the number of moves it took to solve
         * @param par the par number of moves to solve
         */
        void startBlingBling(const float & time, std::size_t moves, std::size_t par);

        /**
         * @brief update callback
         */
        void update(const float & dt);


        /**
         * Call this method to have the button rendered
         */
        void render();

        /**
         * @brief returns the sprite (for testing). I can't figure out how to do the FRIENDS_TEST
         */
        sf::Sprite & getSprite() {
            return sprite;
        }

    private:
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

    };
}
