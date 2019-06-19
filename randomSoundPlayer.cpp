#include "randomSoundPlayer.h"
#include <cassert>

void SlidingTiles::RandomSoundPlayer::loadSounds(const json & jsonArray) {
    for (auto& element : jsonArray) {
        const std::string filename = "assets/" + element["File"].get<std::string>();
        sf::SoundBuffer sb{};
        sb.loadFromFile(filename);
        addSound(sb);
    }
}

void SlidingTiles::RandomSoundPlayer::addSound(const sf::SoundBuffer & soundBuffer) {
    sounds.push_back(soundBuffer);
}

void SlidingTiles::RandomSoundPlayer::playRandomSound() {
    assert(! sounds.empty() && "There are no sounds loaded. Was addSound(sf::SoundBuffer) called?"); // NOLINT (cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(0,sounds.size()-1);
    sound.setBuffer(sounds.at( uniformDistribution(randomNumberGenerator) ));
    sound.play();
}