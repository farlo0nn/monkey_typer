#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

#include "../Enemy.h"

class Spawner {
public:
    Spawner(float spawnDelay, int perWave);

    auto enqueue(const Enemy& enemy) -> void;
    auto update() -> std::vector<Enemy>;
    auto empty() -> bool;
    // void add(const Enemy& enemy);
    // void add(const std::vector<Enemy>& enemies);

private:
    std::queue<Enemy> spawnQueue;
    sf::Clock spawnClock;
    float spawnDelaySeconds;
    int spawnPerWave;
};

