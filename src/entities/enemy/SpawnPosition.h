#pragma once

enum class SpawnPosition {
    UPPER_RIGHT,
    UPPER_LEFT,
    LOWER_LEFT,
    LOWER_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_RIGHT,
    COUNT
};

namespace sp {
    auto get_random_spawn_position() -> SpawnPosition;
}
