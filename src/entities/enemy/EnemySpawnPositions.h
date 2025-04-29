#pragma once


#include "EnemyState.h"
#include <unordered_map>
#include "SFML/System/Vector2.hpp"



// inline const auto ENEMY_SPAWN_POSITIONS = std::unordered_map<SpawnPosition, EnemyState>{
//     {SpawnPosition::UPPER_MIDDLE, EnemyState({WINDOW_SIZE.x / 2.f, 0.f})},
//     {SpawnPosition::UPPER_RIGHT, EnemyState({WINDOW_SIZE.x, 0.f})},
//     {SpawnPosition::MIDDLE_LEFT, EnemyState({0.f, WINDOW_SIZE.y / 2.f})},
//     {SpawnPosition::MIDDLE_RIGHT,  EnemyState({WINDOW_SIZE.x, WINDOW_SIZE.y / 2.f})},
//     {SpawnPosition::LOWER_LEFT, EnemyState({0.f, WINDOW_SIZE.y})},
//     {SpawnPosition::LOWER_MIDDLE,  EnemyState({WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y})}
// };

inline const auto ENEMY_SPAWN_POSITIONS = std::unordered_map<SpawnPosition, EnemyState>{
    {SpawnPosition::UPPER_LEFT, EnemyState(SpawnPosition::UPPER_LEFT)},
    {SpawnPosition::UPPER_RIGHT, EnemyState(SpawnPosition::UPPER_RIGHT)},
    {SpawnPosition::MIDDLE_LEFT, EnemyState(SpawnPosition::MIDDLE_LEFT)},
    {SpawnPosition::MIDDLE_RIGHT,  EnemyState(SpawnPosition::MIDDLE_RIGHT)},
    {SpawnPosition::LOWER_LEFT, EnemyState(SpawnPosition::LOWER_LEFT)},
    {SpawnPosition::LOWER_RIGHT,  EnemyState(SpawnPosition::LOWER_RIGHT)}
};

