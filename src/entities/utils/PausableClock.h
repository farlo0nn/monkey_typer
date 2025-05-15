#pragma once
#include <SFML/Graphics.hpp>


class PausableClock {
    sf::Clock clock;
    sf::Time lastUpdate;
    bool isPaused;
public:
    PausableClock();
    auto pause() -> void;
    auto start() -> void;
    auto reset() -> void;
    auto getElapsedTime() -> sf::Time;
};