#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "gtest/gtest_prod.h"

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class Button {
    public:
        /**
         * @brief Constructor for the button
         * @param takes the filename of the button bitmap as parameter
         */
        Button(const std::string & filename);

        /**
         * @brief set the position of the button
         */
        void setPosition( float x, float y );

        /**
         * Call this method to have the button rendered
         */
        void render();

        /**
         * @brief returns true if the supplied coordinates are within the button area
         * @param mousePosition the position
         * @return true if inside, false if not
         */
        bool mouseReleased(const sf::Vector2i & mousePosition);

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
    };
}
