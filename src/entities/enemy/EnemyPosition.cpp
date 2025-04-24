#include "./EnemyPosition.h"
#include "../../Constants.cpp"

EnemyPosition::EnemyPosition(sf::Vector2f position) {
    this->coordinates = position;
    this->direction = get_direction_to_center(this->coordinates);
}

auto EnemyPosition::get_direction_to_center(sf::Vector2f coordinates) -> sf::Vector2f {
    auto direction = CENTER_POSITION - coordinates;
    auto length = std::hypot(direction.x, direction.y);
    if (length != 0)
        direction /= length;
    return direction;
}
