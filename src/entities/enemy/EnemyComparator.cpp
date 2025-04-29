#include "EnemyComparator.h"
#include "../../Constants.h"
#include <cmath>

bool EnemyComparator::operator()(const Enemy& a, const Enemy& b) const {
    auto const a_position = a.get_sprite().getPosition();
    auto const b_position = b.get_sprite().getPosition();
    float distA = std::hypot(a_position.x - CENTER_POSITION.x, a_position.y - CENTER_POSITION.y);
    float distB = std::hypot(b_position.x - CENTER_POSITION.x, b_position.y - CENTER_POSITION.y);
    return distA < distB;
}