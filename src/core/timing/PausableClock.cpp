#include "PausableClock.h"

PausableClock::PausableClock(): isPaused(false) {
    clock.restart();
    lastUpdate = sf::Time::Zero;
}


auto PausableClock::pause() -> void {
    if (!isPaused) {
        isPaused = true;
        lastUpdate += clock.getElapsedTime();
        clock.stop();
    }
}

auto PausableClock::start() -> void {
    if (isPaused) {
        isPaused = false;
        clock.restart();
    }
}

auto PausableClock::reset() -> void {
    isPaused = false;
    lastUpdate = sf::Time::Zero;
    clock.restart();
}

auto PausableClock::getElapsedTime() -> sf::Time {
    if (isPaused) {
        return lastUpdate;
    }
    return lastUpdate + clock.getElapsedTime();
}
