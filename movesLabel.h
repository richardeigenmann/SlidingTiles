#pragma once

#include "label.h"
#include "zmqSingleton.h"
#include "updatingSingleton.h"
#include "json.hpp"

namespace SlidingTiles {

    /**
     * @brief The Label showing and updating the par
     */
    class MovesLabel : public Label, public Updateable {
    public:

        /**
         * @brief Constructor for the level Label
         */
        MovesLabel();

        /**
         * @brief Destructor
         */
        ~MovesLabel();

        /**
         * @brief update callback
         */
        void update(const float dt) override;

    private:
        /**
         * Tracks the number of moves the user made
         */
        int moves{-1};
        
        /**
         * @brief updates the label
         */
        void updateLabel();

    };
}