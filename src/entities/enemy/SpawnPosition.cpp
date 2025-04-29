#include "SpawnPosition.h"

#include <random>
#include <__random/random_device.h>

auto sp::get_random_spawn_position() -> SpawnPosition {
    std::random_device rdev;
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution<int> dist(0,static_cast<int>(SpawnPosition::COUNT)-1);
    auto spawn_position = static_cast<SpawnPosition>(dist(rgen));
    return spawn_position;
}