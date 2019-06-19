#pragma once

#include "json.hpp"
#include <SFML/Audio.hpp>
#include <random>

using json = nlohmann::json;

namespace SlidingTiles
{

/**
     * @brief Class to hold a collection of sounds offering a method to play a 
     * random sound from the collection.
     */
class RandomSoundPlayer
{
public:
    explicit RandomSoundPlayer()
    {
        // see Book Marius Bancila Modern C++ Programming Cookbook
        std::random_device rd{};
        randomNumberGenerator.seed(rd());
    }
    /**
         * @brief Load method that takes the filenames in the JSON array and loads
         * the corresponding files into the sounds vector.
         * @param jsonArray The JSON array with File entries representing the filenames
         */
    void loadSounds(const json &jsonArray);

    /**
         * @brief adds the supplied sound to the vector of sounds
         * @param soundBuffer
         */
    void addSound(const sf::SoundBuffer &soundBuffer);

    /**
         * @brief plays a random sound from the sounds vector
         */
    void playRandomSound();

private:
    /**
         * @brief The vector holding all the sounds
         */
    std::vector<sf::SoundBuffer> sounds{};

    /**
         * @brief the currently playing sound
         */
    sf::Sound sound{};

    /**
         * @brief add a decent random number Generator to the class
         */
    std::mt19937 randomNumberGenerator;
};

} // namespace SlidingTiles