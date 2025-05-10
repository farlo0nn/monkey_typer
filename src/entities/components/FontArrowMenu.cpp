#include "FontArrowMenu.h"

FontArrowMenu::FontArrowMenu(const sf::Vector2f& position) : BaseArrowMenu(position, {"Arial", "Pixel"}) {}

auto FontArrowMenu::get_value() const -> sf::Font {
    auto path = std::string();
    switch (curValId) {
        case 0: path = "assets/fonts/arial.ttf"; break;
        default: path = "assets/fonts/pixelify-sans.ttf"; break;
    }
    auto font = sf::Font(path);
    return font;
}
