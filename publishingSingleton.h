#pragma once

#include <iostream>
#include <string>
#include "zmq.hpp"

namespace SlidingTiles {

    /**
     * @brief The ZeroMQ publisher for this project
     */
    class PublishingSingleton {
    public:
        /**
         * @brief Deleted to enforce singleton pattern
         */
        PublishingSingleton(PublishingSingleton const&) = delete;

        /**
         * @brief Deleted to enforce singleton pattern
         */
        void operator=(PublishingSingleton const&) = delete;

        /**
         * @brief returns the single instance of the PublishingSingleton
         */
        static PublishingSingleton& getInstance() {
            static PublishingSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

        void publish(std::string message);

        static const std::string PUBLISHER_SOCKET;
        static const std::string RECEIVER_SOCKET;
        
        static const std::string INITIALISING;

        static const std::string GAME_WON;

        static const std::string GAME_STARTED;

    private:
        /**
         * @brief Private constructor for singleton
         */
        PublishingSingleton();

        /**
         * @brief The ZeroMQ context
         */
        zmq::context_t context{1};

        /**
         * @brief The ZeroMQ socket;
         */
        zmq::socket_t socket{context, ZMQ_PUB};


    };

} //namespace
