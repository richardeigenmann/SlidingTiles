#pragma once
#include <iostream>
#include <string>
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "zmqSingleton.h"

namespace SlidingTiles {
    /**
     * @brief A base button class
     */
    class DebugMessageListener : public Updateable {
    public:
        /**
         * @brief Constructor for DebugMessageListener
         */
        DebugMessageListener();

        /**
         * @brief Destructor for DebugMessageListener
         */
        ~DebugMessageListener();

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
