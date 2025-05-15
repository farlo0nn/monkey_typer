//
// Created by Belinskiy Oleksandr on 14.05.2025.
//

#include "Difficulty.h"

#include <iostream>
#include <ostream>

Difficulty::Difficulty() : baseSpeed(60), spawnPerWave(3), spawnDelay(4) {
    calculateScoreMultiplier();
}

auto Difficulty::update(int baseSpeed, int perWave, int spawnDelay) -> void {
    this->baseSpeed = baseSpeed;
    this->spawnPerWave = perWave;
    this->spawnDelay = spawnDelay;
    calculateScoreMultiplier();
}

auto Difficulty::calculateScoreMultiplier() -> void {
    scoreMultiplier = 1.0f + ((baseSpeed - 60) / 60.0f) * 1.0f + ((spawnPerWave - 2) / 4.0f) * 0.9f + ((7.0f - spawnDelay) / 5.0f) * 0.6f;
}

auto Difficulty::show() -> void {
    std::cout << baseSpeed << " " << spawnPerWave << " " << spawnDelay << std::endl;
}