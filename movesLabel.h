#pragma once

#include "label.h"
#include "zmqSingleton.h"
#include "updatingSingleton.h"
#include "json.hpp"
#include "zmqSubscriber.h"

namespace SlidingTiles {

    /**
     * @brief The Label showing and updating the par
     */
    class MovesLabel : public Label, public Updateable, public ZmqSubscriber {
    public:

        /**
         * @brief Constructor for the level Label
         */
        explicit MovesLabel();

        /**
         * @brief Destructor
         */
        ~MovesLabel();

        /**
         * @brief update callback
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

    private:
        /**
         * Tracks the number of moves the user made
         */
        int moves{0};
        
        /**
         * @brief updates the label
         */
        void updateLabel();

    };
}