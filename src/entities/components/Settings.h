#pragma once

#include "SFML/Graphics/Drawable.hpp"

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "DifficultyArrowMenu.h"
#include "FontArrowMenu.h"
#include "MetricDisplay.h"
#include "Slider.h"

enum class SettingsMode {
    SYSTEM,
    ENEMIES
};

class Settings : public sf::Drawable {
    sf::Texture background_texture;
    sf::Font font;
    int characterSize;
    sf::Sprite background;
    Slider fontSizeSlider;
    Slider maxWordLengthSlider;
    Slider minWordLengthSlider;
    MetricDisplay<int> fontSizeDisplay;
    MetricDisplay<int> maxWordLengthDisplay;
    MetricDisplay<int> minWordLengthDisplay;
    sf::Texture button_active_texture;
    sf::Texture button_inactive_texture;
    Button systemSettings;
    Button enemiesSettings;
    Button toMenu;
    DifficultyArrowMenu difficultyArrowMenu;
    FontArrowMenu fontArrowMenu;
    SettingsMode mode;

    float menuScale = 2.0f;

    template<typename  T>
    static auto configure_component(T &component, sf::Vector2f position, float scale) -> void;

    template<typename T>
    static auto configure_component(T& component, sf::Vector2f position, float scalex, float scaley) -> void;

    auto set_mode(const SettingsMode& mode) -> void;

public:

    Settings(const std::string& path_to_settings);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    auto getFontSizeSlider() -> Slider&;
    auto getMaxWordLengthSlider() -> Slider&;
    auto getMinWordLengthSlider() -> Slider&;
    auto loadFromFile(const std::string& path) -> void;
    auto saveToFile(const std::string& path) const -> void;
    auto update() -> void;
    auto getArrowMenus() -> std::vector<BaseArrowMenu*>;
    auto getToMenu() -> Button&;
    auto getSystemSettings() -> Button&;
    auto getEnemiesSettings() -> Button&;
    auto systemSettingsMode() -> bool;
    auto valid() const -> std::pair<bool, std::optional<std::string>>;
};
