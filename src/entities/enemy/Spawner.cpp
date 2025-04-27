#include "Spawner.h"

#include <iostream>

Spawner::Spawner(float spawnDelay, int perWave): spawnDelaySeconds(spawnDelay), spawnPerWave(perWave) {}

auto Spawner::update() -> std::vector<Enemy> {
    auto newEnemies = std::vector<Enemy>();
    if (spawnClock.getElapsedTime().asSeconds() >= spawnDelaySeconds) {
        auto i = int();
        while (i < spawnPerWave && !spawnQueue.empty()) {
            newEnemies.push_back(spawnQueue.front());
            spawnQueue.pop();
            i++;
        }
        spawnClock.restart();
    }
    return newEnemies;
}

auto Spawner::enqueue(const Enemy &enemy) -> void {
    spawnQueue.push(enemy);
}

auto Spawner::empty() -> bool {
    return this->spawnQueue.empty();
}

