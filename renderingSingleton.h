#pragma once

#include <filesystem>
#include "renderable.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <unistd.h>

namespace SlidingTiles
{

/**
     * @brief Singleton class that holds the information about the screen coordinates etc.
     */
class RenderingSingleton
{
public:
    /**
         * @brief Deleted to enforce singleton pattern
         */
    explicit RenderingSingleton(RenderingSingleton const &) = delete;

    /**
         * @brief Deleted to enforce singleton pattern
         */
    void operator=(RenderingSingleton const &) = delete;

    /**
         * @brief returns the single instance of the RenderingSingleton
         */
    static RenderingSingleton &getInstance()
    {
        static RenderingSingleton instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    /**
         * @brief returns a pointer to the render window
         */
    sf::RenderWindow *getRenderWindow()
    {
        return &window;
    }

    /**
         * @brief the 0,0 coordinates of the grid in the window
         */
    sf::Vector2i gridZeroZero{100, 100};

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
    void add(Renderable &renderable) {
        renderables.insert(std::pair<Renderable *const, Renderable *const>(&renderable, &renderable));
    }

    /**
         * Removes a renderable from the list of objects to render
         * @param renderable The Renderable to remove
         */
    void remove(Renderable &renderable) {
        renderables.erase(&renderable);
    }

    /**
     * Tell all renderables to render
     */
    void renderAll() {
        for (auto &pair : renderables)
        {
            if (pair.second->getRenderPriority() == Renderable::RenderPriority::Background)
            {
                pair.second->render();
            }
        }
        for (auto &pair : renderables)
        {
            if (pair.second->getRenderPriority() == Renderable::RenderPriority::Normal)
            {
                pair.second->render();
            }
        }
        for (auto &pair : renderables)
        {
            if (pair.second->getRenderPriority() == Renderable::RenderPriority::OnTop)
            {
                pair.second->render();
            }
        }
        getRenderWindow()->display();
    }

    auto getAssetDir() const noexcept(false) -> std::string  {
        return this->get_executable_path() + "/sliding-tiles-assets/";
    }

private:
    /**
     * @brief Private constructor for singleton
     */
    explicit RenderingSingleton();

    /**
     * @brief the rendering window
     */
    sf::RenderWindow window;

    /**
     * @brief The map of Renderables
     */
    std::map<Renderable *const, Renderable *const> renderables;

    /**
     * @brief Cross platform way to get the path of the executable so we can derive the 
     * asset directory.
     * @see https://en.sfml-dev.org/forums/index.php?topic=12416.msg86622#msg86622
     */
    auto get_executable_path() const noexcept (false) -> std::string {
        char buff[1024];
//#if defined(LINUX)
        ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
        if (len != -1) {
            buff[len] = '\0';
            return std::filesystem::path(buff).parent_path().string();
        } else {
            std::cerr << "Failed to retrieve the executable path." << std::endl;
            return std::filesystem::current_path().string();
        }
/* #elif defined(WINDOWS)
        HMODULE module_handle = GetModuleHandle(nullptr);
        GetModuleFileName(module_handle, buff, sizeof(buff));
        return std::experimental::filesystem::path(buff).parent_path.string();
#else
#error "MISSING CODE :-( - See StackOverflow 1023306"
*/
//#endif
    }
};

} // namespace SlidingTiles
