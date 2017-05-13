#pragma once
#include <iostream>
#include <string>
#include "json.hpp"
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "zmqSingleton.h"
#include "randomSoundPlayer.h"


namespace SlidingTiles {

    /**
     * @brief A class that plays an attitude sound
     */
    class AttitudeSoundPlayer : public RandomSoundPlayer, public Updateable {
    public:
        /**
         * @brief Constructor 
         */
        AttitudeSoundPlayer();

        /**
         * @brief Destructor
         */
        ~AttitudeSoundPlayer();

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

    };
}
