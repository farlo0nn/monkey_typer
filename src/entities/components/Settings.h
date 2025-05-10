#pragma once
#include "SFML/Graphics/Drawable.hpp"

#pragma once

#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "DifficultyArrowMenu.h"
#include "FontArrowMenu.h"
#include "MetricDisplay.h"
#include "Slider.h"

class Settings : public sf::Drawable {
    sf::Texture background_texture;
    sf::Font font;
    int characterSize;
    sf::Sprite background;
    Slider fontSizeSlider;
    MetricDisplay<int> fontSizeDisplay;
    sf::Texture button_active_texture;
    sf::Texture button_inactive_texture;
    Button toMenu;
    DifficultyArrowMenu difficultyArrowMenu;
    FontArrowMenu fontArrowMenu;

    float menuScale = 2.0f;

    template<typename  T>
    static auto configure_component(T &component, sf::Vector2f position, float scale) -> void;
public:

    Settings();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    auto getFontSizeSlider() -> Slider&;
    auto update() -> void;
    auto getArrowMenus() -> std::vector<BaseArrowMenu*>;
    auto getToMenu() -> Button&;
};
