#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "renderingSingleton.h"
#include "renderable.h"

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class Label : public Renderable {
    public:
        /**
         * @brief Constructor for the label
         */
        Label();

        /**
         * @brief Destructor
         */
        ~Label() {
            RenderingSingleton::getInstance().remove(*this);
        }


        /**
         * @brief set the position of the label
         */
        void setPosition(float x, float y);

        /**
         * Call this method to have the label rendered
         */
        void render() override;

        /**
         * @brief sets the text of the label
         * @param newText the new text
         */
        void setText(std::string newText);


    private:

        /**
         * @brief a font to use for the text
         */
        sf::Font font;

        /**
         * @brief the text to print
         */
        sf::Text text;

    };
}