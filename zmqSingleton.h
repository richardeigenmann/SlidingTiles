#pragma once

#include <string>
#include "zmq.hpp"
#include <memory>

namespace SlidingTiles {

    /**
     * @brief The core class providing the ZeroMQ messaging functionality for this
     * application. It is a Singleton so that it exists only once. It allows 
     * anyone to call the publisher for this project
     */
    class ZmqSingleton {
    public:
        /**
         * @brief Deleted Constructor to enforce singleton pattern
         */
        ZmqSingleton(ZmqSingleton const&) = delete;

        /**
         * @brief Deleted Copy Constructor to enforce singleton pattern
         */
        void operator=(ZmqSingleton const&) = delete;

        /**
         * @brief returns the single instance of the PublishingSingleton
         */
        static ZmqSingleton& getInstance() {
            static ZmqSingleton instance;
            return instance;
        }

        /**
         * @brief Publishes the supplied message to all ZMQ receivers
         * @param message The message (in JSON format) to publish
         */
        void publish(const std::string & message);

        /**
         * @brief the socket definition for the publishing socket
         */
        static const std::string PUBLISHER_SOCKET;

        /**
         * @brief the socket definition for the receiving sockets
         */
        static const std::string RECEIVER_SOCKET;


        static const std::string INITIALISING;

        static const std::string GAME_WON;

        static const std::string GAME_STARTED;

        static const std::string SET_TILE;
        static const std::string SLIDE_TILE;
        static const std::string MOUSE_CLICKED;
        
        static const std::string LOAD_NEXT_LEVEL;
        static const std::string LOAD_RANDOM_LEVEL;
        static const std::string RESTART_LEVEL;
        

        /**
         * @brief returns a shared_ptr to the context for the ZeroMQ messaging.
         * For In-Process communication it is vital that the SAME
         * context is used.
         * @return a shared_ptr to the context for ZeroMQ messaging
         */
        std::shared_ptr<zmq::context_t> & getContext() {
            return contextPtr;
        }



    private:
        /**
         * @brief Private constructor for the Singleton
         */
        ZmqSingleton();

        /**
         * @brief A shared_ptr to the context which is the core object for ZeroMQ
         * messaging. For In-Process communication it is vital that the SAME
         * context is used.
         */
        std::shared_ptr<zmq::context_t> contextPtr = std::make_shared<zmq::context_t>(1);

        /**
         * @brief The ZeroMQ socket;
         */
        zmq::socket_t socket{*contextPtr, ZMQ_PUB};


    };

} //namespace
