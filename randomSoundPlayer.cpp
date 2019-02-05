#include "randomSoundPlayer.h"
#include <assert.h>
#include <chrono> // std::chrono::system_clock

using namespace SlidingTiles;

RandomSoundPlayer::RandomSoundPlayer() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomNumberGenerator.seed(seed);
}


void RandomSoundPlayer::loadSounds(const json & jsonArray) {
    for (auto& element : jsonArray) {
        const std::string filename = "assets/" + element["File"].get<std::string>();
        sf::SoundBuffer sb{};
        sb.loadFromFile(filename);
        addSound(sb);
    }
    
}

void RandomSoundPlayer::addSound(const sf::SoundBuffer & soundBuffer) {
    sounds.push_back(soundBuffer);
}

void RandomSoundPlayer::playRandomSound() {
    assert(! sounds.empty() && "There are no sounds loaded. Was addSound(sf::SoundBuffer) called?");
    std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(0,sounds.size()-1);
    sound.setBuffer(sounds.at( uniformDistribution(randomNumberGenerator) ));
    sound.play();
}