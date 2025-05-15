#include "EnemyComparator.h"
#include "../../../Constants.h"
#include <cmath>

bool EnemyComparator::operator()(const Enemy& a, const Enemy& b) const {

    auto lengthA = getPathLength(a);
    auto lengthB = getPathLength(b);
    return lengthA < lengthB;
}

auto EnemyComparator::getPathLength(const Enemy& e) -> float {
    auto e_path = e.get_enemy_state().path;
    auto cur_waypoint = e.get_sprite().getPosition();
    auto lengthA = float();
    for (auto& waypoint : e_path) {
        lengthA += std::hypot(waypoint.x - cur_waypoint.x, waypoint.y - cur_waypoint.y);
    }
    return lengthA;
}
