#include "Spawner.h"

Spawner::Spawner(float spawnDelay, int perWave): spawnDelaySeconds(spawnDelay), spawnPerWave(perWave) {}

auto Spawner::update() -> void {
    if (this->spawnClock.getElapsedTime().asSeconds() >= this->spawnDelaySeconds) {
        for (int i = 0; i < this->spawnPerWave; i++ && !this->spawnQueue.empty()) {
            this->activeEnemies.push_back(this->spawnQueue.front());
            this->spawnQueue.pop();
        }
        this->spawnClock.restart();
    }
}

auto Spawner::enqueue(const Enemy &enemy) -> void {
    this->spawnQueue.push(enemy);
}

const std::vector<Enemy> &Spawner::getActiveEnemies() const {
    return activeEnemies;
}




