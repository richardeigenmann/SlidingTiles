#include "json.hpp"
#include "parLabel.h"
#include "zmqSingleton.h"
#include <sstream>
#include <string_view>

using json = nlohmann::json;

const unsigned int X{400};
const unsigned int Y{180};

/**
 * @brief Constructor for the par label
 */
SlidingTiles::ParLabel::ParLabel() {
  setPosition(X, Y);

  UpdatingSingleton::getInstance().add(*this);
};

SlidingTiles::ParLabel::~ParLabel() {
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::ParLabel::update([[maybe_unused]] const sf::Time deltaTime) {
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(*msg);
  }
}

void SlidingTiles::ParLabel::handleMessage(const json &jsonMessage) {
  auto state = jsonMessage["state"].get<std::string_view>();
  if (state == ZmqSingleton::GAME_STARTED) {
    const int par = jsonMessage["par"];
    std::ostringstream parText{};
    parText << "Par: " << par;
    setText(parText.str());
  }
}