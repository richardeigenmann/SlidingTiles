#pragma once
#include "gameView.h"
#include "gameBoard.h"
#include "winnerBlingBling.h"
#include "gameState.h"
#include "updatingSingleton.h"
#include "debugMessageListener.h"
#include "zmqSubscriber.h"


namespace SlidingTiles {

    /**
     * @brief The main game object. This class acts like the Controller and the 
     * Model in MVC and it owns the view (GameView)
     */
    class Game : public Updateable, public ZmqSubscriber {
    public:
        /**
         * @brief Constructor for the game
         */
        explicit Game();

        /**
         * @brief Destructor for the game
         */
        ~Game();

        /**
         * @brief update call to modify the model with a delta time in seconds
         */
        void update(const float dt) override;

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);

        /**
         * @brief entry point for the game
         */
        void run();

        /**
         * @brief the main gameboard of the game
         */
        SlidingTiles::GameBoard gameBoard{};

        /**
         * @brief the view for the game
         */
        SlidingTiles::GameView gameView;


        /**
         * @brief handler method for when the user wants to play a new random game
         */
        void doRandomGame();

        /**
         * @brief handler for the mouse pressed. Essentially records the coordinates
         */
        void doMousePressed(const sf::Vector2i & mousePosition);

        /**
         * @brief the function that figures out what to do when the mouse was released
         */
        void doMouseReleased(const sf::Vector2i & mousePosition);

        /**
         * Moves a tile (if the GameState is GameState::Playing)
         * @param move the move to make
         */
        void doMove(const Move & move);

        /**
         * @brief increment the move count and update the label
         */
        void incrementMoves();

        /**
         * Sets the move counter and updates the moves label
         * @param newMoves the new number of moves
         */
        void setMoves(std::size_t newMoves);

        /**
         * @brief advance to the next level
         */
        void doLevelUp();

        /**
         * @brief the state of the current game
         */
        GameState gameState{GameState::Initializing};

        /**
         * @brief the winner bling bling
         */
        WinnerBlingBling winnerBlingBling{};

    private:
        /**
         * @brief the clock
         */
        sf::Clock deltaClock;

        /**
         * @brief the position of the mouse press to determine the direction of the slide
         */
        sf::Vector2i mousePositionPressed;

        /**
         * @brief the current level
         */
        std::size_t level{0};

        /**
         * @brief the "array" of levels, loaded from the JSON file
         */
        nlohmann::json levelsArray;

        /**
         * @brief loads the level indicated by the level member variable from the levelsArray
         */
        void loadLevel();

        /**
         * @brief restarts the level
         */
        void onRestartButtonClick();

        /**
         * @brief The number of tiles in each direction
         */
        static constexpr float VICTORY_ROLL_TIME = {1.8f};

        /**
         *@brief The amount of time left for the victory roll in seconds.  
         */
        float victoryRollingTime{0.0f};

        /**
         * @brief the number of moves in the game
         */
        std::size_t moves{0};

        /**
         * Creates a DebugMessageListener which listens to the messages published on the ZMQ bus
         */
        DebugMessageListener debugMessageListener;
    };
}
