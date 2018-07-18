#pragma once

#include "label.h"
#include "zmqSingleton.h"
#include "updatingSingleton.h"
#include "json.hpp"

namespace SlidingTiles {

    /**
     * @brief The Label showing and updating the par
     */
    class ParLabel : public Label, public Updateable {
    public:

        /**
         * @brief Constructor for the level Label
         */
        ParLabel();

        /**
         * @brief Destructor
         */
        ~ParLabel();

        /**
         * @brief update callback
         */
        void update(const float dt) override;
    };
}