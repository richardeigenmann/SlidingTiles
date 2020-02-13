#pragma once

#include <string>

/**
 * @brief returns the executable path of the current binary
 */
auto my_executable_path() noexcept (false) -> std::string;

/**
 * @brief returns the asset directory for the game
 */
auto getAssetDir() noexcept(false) -> std::string;