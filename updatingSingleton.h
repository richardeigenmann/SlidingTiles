#pragma once

#include "updateable.h"
#include <map>

namespace SlidingTiles {

    /**
     * @brief Singleton class that calls the updatables
     */
    class UpdatingSingleton {
    public:
        /**
         * @brief Deleted to enforce singleton pattern
         */
        UpdatingSingleton(UpdatingSingleton const&) = delete;

        /**
         * @brief Deleted to enforce singleton pattern
         */
        void operator=(UpdatingSingleton const&) = delete;

        /**
         * @brief returns the single instance of the UpdatingSingleton
         */
        static UpdatingSingleton& getInstance() {
            static UpdatingSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

        /**
         * Add a Updateable to the list of object to update
         * @param updateable The Updateable to add
         */
        void add(Updateable& updateable) {
            updateables.insert(std::pair<Updateable * const, Updateable * const>(&updateable, &updateable));
        }

        /**
         * Removes a Updateable from the list of objects to update
         * @param updateable The Updateable to remove
         */
        void remove(Updateable& updateable) {
            updateables.erase(&updateable);
        }

        /**
         * Tell all Updateables to render
         */
        void updateAll(const float dt) {
            for (auto& pair : updateables) {
                pair.second->update(dt);

            }
        }

    private:
        /**
         * @brief Private constructor for singleton
         */
        UpdatingSingleton() {};

        /**
         * @brief The map of Updateable
         */
        std::map<Updateable * const, Updateable * const> updateables;

    };

} //namespace
