#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

#include "Enemy.h"

class Spawner {
public:
    Spawner(float spawnDelay, int perWave);

    void enqueue(const Enemy& enemy);
    void update();
    auto get_active_enemies() -> std::vector<Enemy>&;

private:
    std::queue<Enemy> spawnQueue;
    std::vector<Enemy> activeEnemies;
    sf::Clock spawnClock;
    float spawnDelaySeconds;
    int spawnPerWave;
};

