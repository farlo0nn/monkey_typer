#pragma once
#include "BaseArrowMenu.h"

class DifficultyArrowMenu : public BaseArrowMenu {
public:
    DifficultyArrowMenu(const sf::Vector2f &position);
    auto getValue() const -> std::string;
    auto setValue(const std::string &value) -> void;
};