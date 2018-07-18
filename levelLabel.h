#pragma once

#include "label.h"
#include "updatingSingleton.h"

namespace SlidingTiles {

    /**
     * @brief The Label showing and updating the level
     */
    class LevelLabel : public Label, public Updateable {
    public:

        /**
         * @brief Constructor for the level label
         */
        LevelLabel();

        /**
         * @brief Destructor
         */
        ~LevelLabel();

        /**
         * @brief update callback from ZeroMQ
         */
        void update(const float dt) override;

    private:
        /**
        * @brief sets the label to the text Level: n 
        * @param level The new level
        */
        void setLevel( int level );

    };
}