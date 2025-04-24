#pragma once

#include "EnemyPosition.h"
#include "../../Constants.cpp"
#include "SFML/System/Vector2.hpp"


enum class SpawnPosition {
    UPPER_RIGHT,
    UPPER_MIDDLE,
    LOWER_LEFT,
    LOWER_MIDDLE,
    MIDDLE_LEFT,
    MIDDLE_RIGHT,
    COUNT
};

inline const auto ENEMY_SPAWN_POSITIONS = std::unordered_map<SpawnPosition, EnemyPosition>{
    {SpawnPosition::UPPER_MIDDLE, EnemyPosition({WINDOW_SIZE.x / 2.f, 0.f})},
    {SpawnPosition::UPPER_RIGHT, EnemyPosition({WINDOW_SIZE.x, 0.f})},
    {SpawnPosition::MIDDLE_LEFT, EnemyPosition({0.f, WINDOW_SIZE.y / 2.f})},
    {SpawnPosition::MIDDLE_RIGHT,  EnemyPosition({WINDOW_SIZE.x, WINDOW_SIZE.y / 2.f})},
    {SpawnPosition::LOWER_LEFT, EnemyPosition({0.f, WINDOW_SIZE.y})},
    {SpawnPosition::LOWER_MIDDLE,  EnemyPosition({WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y})}
};

namespace SpawnPositions {
    auto get_random_spawn_position() -> SpawnPosition;
}
