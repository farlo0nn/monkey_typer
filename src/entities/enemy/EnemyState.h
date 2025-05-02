#pragma once

#include <stack>

#include "Directions.h"
#include "SpawnPosition.h"
#include "SFML/System/Vector2.hpp"

class EnemyState {
    auto add_waypoint(sf::Vector2f point) -> void;
    auto get_direction(sf::Vector2f c1, sf::Vector2f c2)->sf::Vector2f;
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    Directions texture_direction;
    std::deque<sf::Vector2<float>> path;
    EnemyState(SpawnPosition position, Directions texture_direction);

    auto advance_to_next_waypoint() -> void;
    auto has_reached_point() const -> bool;
};
