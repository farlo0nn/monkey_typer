#include "FontArrowMenu.h"

FontArrowMenu::FontArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Arial", "Pixel", "Miners", "64"}) {}

auto FontArrowMenu::getValue() const -> std::string {
    return values[curValId];
}

auto FontArrowMenu::setValue(const std::string& value) -> void {
    auto it = std::ranges::find(values, value);
    if (it != values.end()) {
        curValId = std::distance(values.begin(), it);
    }
    else {
        curValId = 0;
    }
    updateValueLabel();
}
