#include "DifficultyArrowMenu.h"

#include <iostream>

DifficultyArrowMenu::DifficultyArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Easy", "Medium", "Hard", "Extreme"}) {}

auto DifficultyArrowMenu::getValue() const -> std::string {
    // Difficulty difficulty;
    // switch (curValId) {
    //     case 0: difficulty = Difficulty::EASY; break;
    //     case 1: difficulty = Difficulty::MEDIUM; break;
    //     case 2: difficulty = Difficulty::HARD; break;
    //     default: difficulty = Difficulty::EXTREME; break;
    // }
    return values[curValId];

}

auto DifficultyArrowMenu::setValue(const std::string &value) -> void {
    auto it = std::ranges::find(values, value);

    if (it != values.end()) {
        curValId = std::distance(values.begin(), it);
    }
    else {
        curValId = 0;
    }

    updateValueLabel();
}

inline auto to_string(Difficulty d) -> std::string {
    switch (d) {
        case Difficulty::EASY: return "Easy";
        case Difficulty::MEDIUM: return "Medium";
        case Difficulty::HARD: return "Hard";
        case Difficulty::EXTREME: return "Extreme";
        default: throw std::invalid_argument("Unknown Difficulty");
    }
}

inline auto from_string(const std::string& str) -> Difficulty {
    if (str == "Easy") return Difficulty::EASY;
    if (str == "Medium") return Difficulty::MEDIUM;
    if (str == "Hard") return Difficulty::HARD;
    if (str == "Extreme") return Difficulty::EXTREME;
    throw std::invalid_argument("Unknown string for Difficulty: " + str);
}