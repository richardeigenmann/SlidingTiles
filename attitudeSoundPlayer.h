#pragma once
#include "updatingSingleton.h"
#include "randomSoundPlayer.h"
#include "zmqSubscriber.h"

using json = nlohmann::json;
namespace SlidingTiles {

    /**
     * @brief A class that plays an attitude sound
     */
    class AttitudeSoundPlayer : public RandomSoundPlayer, public Updateable, public ZmqSubscriber {
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

        /**
         * @brief handle a new ZMQ message
         */
        void handleMessage(const json & jsonMessage);
   };
}
