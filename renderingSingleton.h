#pragma once

#include <SFML/Graphics.hpp>
#include "renderable.h"
#include <map>

namespace SlidingTiles {

    /**
     * @brief Singleton class that holds the information about the screen coordinates etc.
     */
    class RenderingSingleton {
    public:
        /**
         * @brief Deleted to enforce singleton pattern
         */
        RenderingSingleton(RenderingSingleton const&) = delete;

        /**
         * @brief Deleted to enforce singleton pattern
         */
        void operator=(RenderingSingleton const&) = delete;

        /**
         * @brief returns the single instance of the RenderingSingleton
         */
        static RenderingSingleton& getInstance() {
            static RenderingSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

        /**
         * @brief sets the render window
         *
        void setRenderWindow(sf::RenderWindow* newWindow) {
            window = newWindow;
        }*/

        /**
         * @brief returns a pointer to the render window
         */
        sf::RenderWindow* getRenderWindow() {
            return &window;
        }

        /**
         * @brief the 0,0 coordinates of the grid in the window
         */
        sf::Vector2i gridZeroZero{ 100, 100};

        /**
         * @brief the size of the tiles in pixels
         */
        static const int tileSize{60};

        /**
         * @brief calculate the coordinates for a tile from the x and y position
         */
        sf::Vector2i calculateCoordinates(sf::Vector2i xy);

        /**
         * @brief calculate the coordinates for a tile from the x and y position
         */
        sf::Vector2i calculateCoordinates(int x, int y);

        /**
         * @brief figure out the tile coordinates for a given screen position
         * if position is outside the grid return -1, -1
         */
        sf::Vector2i findTile(sf::Vector2i mousePosition);

        /**
         * Add a Renderable to the list of object to render
         * @param renderable The Renderable to add
         */
        void add(Renderable& renderable) {
            renderables.insert(std::pair<Renderable * const, Renderable * const>(&renderable, &renderable));
        }

        /**
         * Removes a renderable from the list of objects to render
         * @param renderable The Renderable to remove
         */
        void remove(Renderable& renderable) {
            renderables.erase(&renderable);
        }

        /**
         * Tell all renderables to render
         */
        void renderAll() {
            for (auto& pair : renderables) {
                if (pair.second->getRenderPriority() == Renderable::RenderPriority::Background) {
                    pair.second->render();
                }
            }
            for (auto& pair : renderables) {
                if (pair.second->getRenderPriority() == Renderable::RenderPriority::Normal) {
                    pair.second->render();
                }
            }
            for (auto& pair : renderables) {
                if (pair.second->getRenderPriority() == Renderable::RenderPriority::OnTop) {
                    pair.second->render();
                }
            }
            getRenderWindow()->display();
        }

    private:
        /**
         * @brief Private constructor for singleton
         */
        RenderingSingleton();

        /**
         * @brief the rendering window
         */
        sf::RenderWindow window;

        /**
         * @brief The map of Renderables
         */
        std::map<Renderable * const, Renderable * const> renderables;

    };

} //namespace
