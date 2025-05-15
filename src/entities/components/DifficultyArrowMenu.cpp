#include "DifficultyArrowMenu.h"

#include <iostream>

DifficultyArrowMenu::DifficultyArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Easy", "Medium", "Hard", "Extreme"}) {}

auto DifficultyArrowMenu::getValue() const -> std::string {
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