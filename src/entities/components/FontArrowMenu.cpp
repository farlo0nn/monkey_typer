#include "FontArrowMenu.h"

FontArrowMenu::FontArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Arial", "Pixel"}) {}

auto FontArrowMenu::getValue() const -> std::string {
    auto path = std::string();
    switch (curValId) {
        case 0: path = "assets/fonts/arial.ttf"; break;
        default: path = "assets/fonts/pixelify-sans.ttf"; break;
    }
    // auto font = sf::Font(path);
    return values[curValId];
}

auto FontArrowMenu::setValue(std::string value) -> void {
    auto it = std::ranges::find(values, value);
    if (it != values.end()) {
        curValId = std::distance(values.begin(), it);
    }
    else {
        curValId = 0;
    }
    updateValueLabel();
}
