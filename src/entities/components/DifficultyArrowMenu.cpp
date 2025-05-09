#include "DifficultyArrowMenu.h"

DifficultyArrowMenu::DifficultyArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Easy", "Medium", "Hard", "Extreme"}) {}

auto DifficultyArrowMenu::get_value() const -> Difficulty {
    Difficulty difficulty;
    switch (curValId) {
        case 0: difficulty = Difficulty::EASY; break;
        case 1: difficulty = Difficulty::MEDIUM; break;
        case 2: difficulty = Difficulty::HARD; break;
        default: difficulty = Difficulty::EXTREME; break;
    }
    return difficulty;
}
