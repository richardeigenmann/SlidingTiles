#pragma once
#include "strongTypes.h"
#include "renderingSingleton.h"
#include "updatingSingleton.h"
#include "zmqSubscriber.h"
#include <SFML/Graphics.hpp>
#include <string_view>

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class Button : public Renderable, public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for the button
         * @param textureFilename takes the filename of the button bitmap as parameter
         * @param command to issue when clicked
         */
        explicit Button(const AssetPath & textureFilename, const std::string_view command);

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

        /**
         * @brief handle a new ZMQ message
         */
        virtual void handleMessage(const json & jsonMessage);

        /**
         * @brief helps the render function decide if it should render the button
         */
        bool isVisible {true};

    private:
        /**
         * @brief The texture of the button
         */
        std::unique_ptr<sf::Texture> texture;

        /**
         * @brief The sprite of the button
         */
        sf::Sprite sprite;
      
        /**
         * @brief the command to send via ZMQ when the button is clicked
         */
        std::string command;
    };
}
