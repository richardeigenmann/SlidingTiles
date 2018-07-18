#pragma once
#include "updatingSingleton.h"
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
    };
}
