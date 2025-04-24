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
    const std::vector<Enemy>& get_active_enemies() const;

private:
    std::queue<Enemy> spawnQueue;
    std::vector<Enemy> activeEnemies;
    sf::Clock spawnClock;
    float spawnDelaySeconds;
    int spawnPerWave;
};

