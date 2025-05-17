#pragma once


#include "EnemyState.h"
#include "Directions.h"
#include <unordered_map>

inline const auto ENEMY_SPAWN_STATES = std::unordered_map<SpawnPosition, EnemyState>{
    {SpawnPosition::UPPER_LEFT, EnemyState(SpawnPosition::UPPER_LEFT, Directions::LEFT)},
    {SpawnPosition::UPPER_RIGHT, EnemyState(SpawnPosition::UPPER_RIGHT, Directions::RIGHT)},
    {SpawnPosition::MIDDLE_LEFT, EnemyState(SpawnPosition::MIDDLE_LEFT, Directions::LEFT)},
    {SpawnPosition::MIDDLE_RIGHT,  EnemyState(SpawnPosition::MIDDLE_RIGHT, Directions::RIGHT)},
    {SpawnPosition::LOWER_LEFT, EnemyState(SpawnPosition::LOWER_LEFT, Directions::LEFT)},
    {SpawnPosition::LOWER_RIGHT,  EnemyState(SpawnPosition::LOWER_RIGHT, Directions::RIGHT)},
};

