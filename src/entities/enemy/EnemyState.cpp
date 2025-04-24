#include "./EnemyState.h"
#include "../../Constants.cpp"

EnemyState::EnemyState(sf::Vector2f position) {
    this->position = position;
    this->direction = get_direction_to_center(this->position);
}

auto EnemyState::get_direction_to_center(sf::Vector2f coordinates) -> sf::Vector2f {
    auto direction = CENTER_POSITION - coordinates;
    auto length = std::hypot(direction.x, direction.y);
    if (length != 0)
        direction /= length;
    return direction;
}
