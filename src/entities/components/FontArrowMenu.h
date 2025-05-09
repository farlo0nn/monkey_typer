#pragma once
#include "BaseArrowMenu.h"
#include "../../core/Difficulties.h"

class FontArrowMenu : public BaseArrowMenu {
public:
    FontArrowMenu(const sf::Vector2f &position);
    auto get_value() const -> sf::Font;
};
