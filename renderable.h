#pragma once

namespace SlidingTiles {

    /**
     * @brief Interface that defines what a TileObserver must implement
     */
    class Renderable {
    public:

        /**
         * @brief Implementing classes must define the render method
         */
        virtual void render() = 0;

        /**
         * @brief an enum to hold the priority of the renderable. It can be
         * Background, Normal and OnTop. This is the order in which the
         * renderables will be drawn.
         */
        enum RenderPriority {
            Background,
            Normal,
            OnTop
        };


        /**
         * Inheriting classes can override this function to change the priority.
         * @return The RenderPriority enum value
         */
        virtual RenderPriority getRenderPriority() {
            return RenderPriority::Normal;
        }
        
        
        /**
         * Returns the renderable priority in a string
         * @return 
         */
        std::string toString() {
            if (getRenderPriority() == RenderPriority::Background) {
                return "RenderPriority::Background";
            } else if (getRenderPriority() == RenderPriority::Normal) {
                return "RenderPriority::Normal";
            } else {
                return "RenderPriority::OnTop";
            }
            return "Something went wrong";
        }
    };

} // namespace SlidingTiles
