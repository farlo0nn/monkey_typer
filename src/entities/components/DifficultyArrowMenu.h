#pragma once
#include "BaseArrowMenu.h"
#include "../../core/Difficulties.h"

class DifficultyArrowMenu : public BaseArrowMenu {
public:
    DifficultyArrowMenu(const sf::Vector2f &position);
    auto get_value() const -> Difficulty;
};
