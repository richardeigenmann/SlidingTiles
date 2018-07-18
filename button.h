#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "renderingSingleton.h"
#include "updatingSingleton.h"

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class Button : public Renderable, public Updateable {
    public:
        /**
         * @brief Constructor for the button
         * @param textureFilename takes the filename of the button bitmap as parameter
         * @param command to issue when clicked
         */
        Button(const std::string & textureFilename, const std::string & command);

        /**
         * @brief Destructor
         */
        ~Button();

        /**
         * @brief set the position of the button
         */
        void setPosition(float x, float y);

        /**
         * Call this method to have the button rendered
         */
        void render() override;

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

        /**
         * @brief update callback
         */
        void update(const float dt) override;

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
         * @brief the command to send when the button is clicked
         */
        const std::string command;
    };
}
