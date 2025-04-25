#include "Spawner.h"

#include <iostream>

Spawner::Spawner(float spawnDelay, int perWave): spawnDelaySeconds(spawnDelay), spawnPerWave(perWave) {}

auto Spawner::update() -> void {
    if (spawnClock.getElapsedTime().asSeconds() >= spawnDelaySeconds) {
        auto i = int();
        while (i < spawnPerWave && !spawnQueue.empty()) {
            activeEnemies.push_back(spawnQueue.front());
            spawnQueue.pop();
            std::cout << activeEnemies.size() << std::endl;
            i++;
        }
        spawnClock.restart();
    }
}

auto Spawner::enqueue(const Enemy &enemy) -> void {
    spawnQueue.push(enemy);
}

auto Spawner::get_active_enemies() -> std::vector<Enemy>&{
    return activeEnemies;
}




