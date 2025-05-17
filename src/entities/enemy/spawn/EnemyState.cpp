#include "../spawn/EnemyState.h"

#include <queue>
#include "../../../Constants.h"

EnemyState::EnemyState(SpawnPosition position, Directions texture_direction) {

    this->texture_direction = texture_direction;
    this->path = std::deque<sf::Vector2f>();

    switch (position) {
        case SpawnPosition::UPPER_LEFT:
            this->position = {2.4*60, 0.f};
            addWaypoint({2.5*60.f, 2.1*60.f});
            addWaypoint({8.7*60.f, 2.1*60.f});
            addWaypoint({8.7*60.f, WINDOW_SIZE.y/2});
        break;
        case SpawnPosition::UPPER_RIGHT:
            this->position = {14.5*60, 0.f};
            addWaypoint({14.5*60.f, 3.4*60.f});
            addWaypoint({10.9*60.f, 3.4*60.f});
            addWaypoint({10.9*60.f, 2.1*60.f});
            addWaypoint({8.7*60.f, 2.1*60.f});
            addWaypoint({8.7*60.f, WINDOW_SIZE.y/2});
        break;
        case SpawnPosition::LOWER_LEFT:
            this->position = {0.f, 10*60.f};
            addWaypoint({4.5*60.f, 10*60.f});
            addWaypoint({4.5*60.f, 7.6*60.f});
            addWaypoint({8.7*60.f, 7.6*60.f});
            addWaypoint({8.7*60.f, WINDOW_SIZE.y/2});
        break;
        case SpawnPosition::LOWER_RIGHT:
            this->position = {13*60.f, 11*60.f};
            addWaypoint({13*60.f, 9.3*60.f});
            addWaypoint({8.7*60.f, 9.3*60.f});
            addWaypoint({8.7*60.f, WINDOW_SIZE.y/2});
        break;
        case SpawnPosition::MIDDLE_LEFT:
            this->position = {0.f, 5.5*60.f};
            addWaypoint({WINDOW_SIZE.x/2.f, 5.5*60.f});
        break;
        case SpawnPosition::MIDDLE_RIGHT:
            this->position = {WINDOW_SIZE.x, 5.5*60.f};
            addWaypoint({WINDOW_SIZE.x/2.f, 5.5*60.f});
        break;
        default: break;
    }

    this->direction = getDirection(this->position, path.front());
}

auto EnemyState::getDirection(sf::Vector2f c1, sf::Vector2f c2) -> sf::Vector2f {
    auto direction = c2 - c1;
    auto length = std::hypot(direction.x, direction.y);
    if (length != 0)
        direction /= length;
    return direction;
}

auto EnemyState::addWaypoint(sf::Vector2f point) -> void {
    path.push_back(point);
}

auto EnemyState::advanceToNextWaypoint() -> void {
    if (!path.empty()) {
        path.pop_front();
        if (!path.empty())
            direction = getDirection(position, path.front());
        else
            direction = {0.f, 0.f}; // Stop moving
    }
}

auto EnemyState::hasReachedPoint() const -> bool {
    if (path.empty()) return false;
    auto dx = position.x - path.front().x;
    auto dy = position.y - path.front().y;
    return std::hypot(dx, dy) < 5.f;
}


