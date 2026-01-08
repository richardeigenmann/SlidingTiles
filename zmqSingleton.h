#pragma once

#include "json.hpp"
#include "zmq.hpp"
#include <memory>
#include <string_view>

using json = nlohmann::json;

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
        explicit ZmqSingleton(ZmqSingleton const&) = delete;

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
        void publish(const json & message);

        /**
         * @brief the socket definition for the publishing socket
         */
        //const std::string SlidingTiles::ZmqSingleton::PUBLISHER_SOCKET = "tcp://*:64123";
        static inline std::string_view PUBLISHER_SOCKET = "inproc://#1";

        /**
         * @brief the socket definition for the receiving sockets
         */
        // const std::string SlidingTiles::ZmqSingleton::RECEIVER_SOCKET = "tcp://localhost:64123";
        static inline std::string_view RECEIVER_SOCKET = "inproc://#1";

        /**
         * @brief the configuration has been loaded
         */
        static inline std::string_view CONFIGURATION_LOADED = "Configuration Loaded";

        /**
         * @brief the Game was won
         */
        static inline std::string_view GAME_WON = "Game Won";

        /**
         * @brief signifies that the game has started
         */
        static inline std::string_view GAME_STARTED = "Game Started";

        /**
         * @brief signifies that the game has gone over par
         */
        static inline std::string_view OVER_PAR = "Over Par";

        /**
         * @brief set a specific tile
         */
        static inline std::string_view SET_TILE = "Set Tile";

        /**
         * @brief slide the tile as specified in the details of the message
         */
        static inline std::string_view SLIDE_TILE = "Slide Tile";

        /**
         * @brief the mouse was clicked further information available in the message
         */
        static inline std::string_view MOUSE_CLICKED = "Mouse Clicked";

        /**
         * @brief load the next level
         */
        static inline std::string_view LOAD_NEXT_LEVEL = "Load Next Level";

        /**
         * @brief search for a new random level and start to play it
         */
        static inline std::string_view LOAD_RANDOM_LEVEL = "Load Random Level";

        /**
         * @brief undo the last move
         */
        static inline std::string_view UNDO_MOVE = "Undo Move";

        /**
         * @brief restart the same level
         */
        static inline std::string_view RESTART_LEVEL = "Restart Level";

        /**
         * @brief broadcast moves count
         */
        static inline std::string_view BROADCAST_MOVES_COUNT = "Broadcast Moves Count";

        /**
         * @brief when sent instructs the listening objects to output debug information
         */
        static inline std::string_view DEBUG = "Debug";

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
        explicit ZmqSingleton();

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
