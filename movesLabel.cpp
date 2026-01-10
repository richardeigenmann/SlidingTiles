#include "movesLabel.h"
#include "json.hpp"
#include "zmqSingleton.h"
#include <cstddef>
#include <sstream>
#include <string_view>

using json = nlohmann::json;


const unsigned int X{400};
const unsigned int Y{150};

/**
 * @brief Constructor for the moves label
 */
SlidingTiles::MovesLabel::MovesLabel() {
  setPosition(X, Y);
  UpdatingSingleton::getInstance().add(*this);
  updateLabel();
};

SlidingTiles::MovesLabel::~MovesLabel() {
  UpdatingSingleton::getInstance().remove(*this);
}

void SlidingTiles::MovesLabel::update([[maybe_unused]] const sf::Time deltaTime) {
  auto msg = getZmqMessage();
  if (msg) {
    handleMessage(*msg);
  }
}

void SlidingTiles::MovesLabel::handleMessage(const json &jsonMessage) {
  auto state = jsonMessage["state"].get<std::string_view>();
  if (state == SlidingTiles::ZmqSingleton::BROADCAST_MOVES_COUNT) {
    moves = jsonMessage["count"].get<size_t>();
    updateLabel();
  }
}

void SlidingTiles::MovesLabel::updateLabel() {
  std::ostringstream movesText{};
  movesText << "Moves: " << moves;
  setText(movesText.str());
}