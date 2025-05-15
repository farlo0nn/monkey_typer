#pragma once
#include "../Enemy.h"

struct EnemyComparator {
    bool operator()(const Enemy& a, const Enemy& b) const;
    static auto getPathLength(const Enemy& e) -> float;
};
