#pragma once
#include <string>

struct Difficulty {

    double scoreMultiplier;
    int baseSpeed;
    int spawnPerWave;
    int spawnDelay;
    Difficulty();
    auto update(int baseSpeed, int perWave, int spawnDelay) -> void;
    auto show() -> void;
private:
    auto calculateScoreMultiplier() -> void;
};
