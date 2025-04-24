#pragma once

#include "EnemyState.h"
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

inline const auto ENEMY_SPAWN_POSITIONS = std::unordered_map<SpawnPosition, EnemyState>{
    {SpawnPosition::UPPER_MIDDLE, EnemyState({WINDOW_SIZE.x / 2.f, 0.f})},
    {SpawnPosition::UPPER_RIGHT, EnemyState({WINDOW_SIZE.x, 0.f})},
    {SpawnPosition::MIDDLE_LEFT, EnemyState({0.f, WINDOW_SIZE.y / 2.f})},
    {SpawnPosition::MIDDLE_RIGHT,  EnemyState({WINDOW_SIZE.x, WINDOW_SIZE.y / 2.f})},
    {SpawnPosition::LOWER_LEFT, EnemyState({0.f, WINDOW_SIZE.y})},
    {SpawnPosition::LOWER_MIDDLE,  EnemyState({WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y})}
};

namespace SpawnPositions {
    auto get_random_spawn_position() -> SpawnPosition;
}
