#pragma once
#include <iostream>
#include <string>
#include "zmq.hpp"
#include "updatingSingleton.h"
#include "publishingSingleton.h"

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
         * @brief ZeroMQ needs a context
         */
        //zmq::context_t context{1};
        zmq::context_t * context;
        
        /**
         * @brief the ZeroMQ socket of type subscriber
         */
        //zmq::socket_t socket{context, ZMQ_SUB};
        zmq::socket_t * socket;
        

    };
}
