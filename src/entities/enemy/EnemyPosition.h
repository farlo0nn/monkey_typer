#pragma once

#include "SFML/System/Vector2.hpp"

class EnemyPosition {
public:
    sf::Vector2f coordinates;
    sf::Vector2f direction;
    EnemyPosition(sf::Vector2f coordinates);

private:
    auto get_direction_to_center(sf::Vector2f coordinates)->sf::Vector2f;
};
