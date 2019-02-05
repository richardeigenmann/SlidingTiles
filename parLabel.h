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
    class ParLabel : public Label, public Updateable, public ZmqSubscriber {
    public:

        /**
         * @brief Constructor for the level Label
         */
        explicit ParLabel();

        /**
         * @brief Destructor
         */
        ~ParLabel();

        /**
         * @brief update callback
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);
    };
}