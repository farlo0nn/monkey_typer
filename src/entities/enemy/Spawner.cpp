#include "Spawner.h"

#include <iostream>

Spawner::Spawner(float spawnDelay, int perWave): spawnDelaySeconds(spawnDelay), spawnPerWave(perWave) {}

auto Spawner::update() -> void {
    if (this->spawnClock.getElapsedTime().asSeconds() >= this->spawnDelaySeconds) {
        auto i = int();
        while (i < this->spawnPerWave && !this->spawnQueue.empty()) {
            this->activeEnemies.push_back(this->spawnQueue.front());
            this->spawnQueue.pop();
            std::cout << this->activeEnemies.size() << std::endl;
            i++;
        }
        this->spawnClock.restart();
    }
}

auto Spawner::enqueue(const Enemy &enemy) -> void {
    this->spawnQueue.push(enemy);
}

const std::vector<Enemy>& Spawner::get_active_enemies() const {
    return activeEnemies;
}




