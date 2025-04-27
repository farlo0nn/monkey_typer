#pragma once
#include "Enemy.h"

struct EnemyPriority {
    bool operator()(const Enemy& a, const Enemy& b) const;
};
