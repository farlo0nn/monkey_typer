#include "EnemyPriority.h"
#include <cmath>

bool EnemyPriority::operator()(const Enemy& a, const Enemy& b) const {
    auto const a_position = a.get_sprite().getPosition();
    auto const b_position = b.get_sprite().getPosition();
    float distA = std::hypot(a_position.x - 0, a_position.y - 0);
    float distB = std::hypot(b_position.x - 0, b_position.y - 0);
    return distA > distB;
}