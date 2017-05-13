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
         * @brief A shared_ptr to the context of the ZeroMQ. It gets set by
         * the Constructor
         */
        std::shared_ptr<zmq::context_t> contextPtr;

        /**
         * @brief The ZeroMQ socket of type subscriber. It is set by the 
         * constructor.
         */
        std::unique_ptr<zmq::socket_t> socket;
        
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