#include "levelLabel.h"
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;

/**
 * @brief Constructor for the level Label
 */
SlidingTiles::LevelLabel::LevelLabel() {
  const unsigned int X{400};
  const unsigned int Y{120};
  setPosition(X, Y);

  SlidingTiles::UpdatingSingleton::getInstance().add(*this);
};

SlidingTiles::LevelLabel::~LevelLabel() {
  SlidingTiles::UpdatingSingleton::getInstance().remove(*this);
}

/**
 * Listens for the ZmqSingleton::GAME_STARTED message and updates the level
 * label
 */
void SlidingTiles::LevelLabel::update(
    const float dt) { // NOLINT (misc-unused-parameters)
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(msg.value());
  }
}

void SlidingTiles::LevelLabel::handleMessage(const json &jsonMessage) {
  auto state = jsonMessage["state"].get<std::string>();
  if (state == SlidingTiles::ZmqSingleton::GAME_STARTED) {
    int level = jsonMessage["level"];
    setLevel(level);
  }
}

/**
 * sets the label to the text Level: n
 */
void SlidingTiles::LevelLabel::setLevel(int level) {
  std::ostringstream levelText{};
  levelText << "Level: " << level;
  setText(levelText.str());
}