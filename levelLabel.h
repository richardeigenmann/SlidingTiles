#pragma once

#include "label.h"
#include "zmqSingleton.h"
#include "updatingSingleton.h"
#include "json.hpp"

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
        * @brief sets the label to the text Level: n 
        * @param level The new level
        */
        void setLevel( int level );

    };
}