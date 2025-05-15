#pragma once
#include "BaseArrowMenu.h"

class FontArrowMenu : public BaseArrowMenu {
public:
    FontArrowMenu(const sf::Vector2f &position);
    auto getValue() const -> std::string override;
    auto setValue(const std::string& value) -> void override;
};
