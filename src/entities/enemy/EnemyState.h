#pragma once

#include "SFML/System/Vector2.hpp"

class EnemyState {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    EnemyState(sf::Vector2f coordinates);

private:
    auto get_direction_to_center(sf::Vector2f coordinates)->sf::Vector2f;
};
