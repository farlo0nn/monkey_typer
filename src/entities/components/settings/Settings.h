#pragma once

#include "SFML/Graphics/Drawable.hpp"

#include "../buttons/Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "../arrowMenus/DifficultyArrowMenu.h"
#include "../arrowMenus/FontArrowMenu.h"
#include "../displays/MetricDisplay.h"
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
    Slider baseSpeedSlider;
    Slider waveDelaySlider;
    Slider perWaveSlider;
    MetricDisplay<int> fontSizeDisplay;
    MetricDisplay<int> maxWordLengthDisplay;
    MetricDisplay<int> minWordLengthDisplay;
    MetricDisplay<int> baseSpeedDisplay;
    MetricDisplay<int> waveDelayDisplay;
    MetricDisplay<int> perWaveDisplay;
    sf::Texture button_active_texture;
    sf::Texture button_inactive_texture;
    Button systemSettings;
    Button enemiesSettings;
    Button toMenu;
    // DifficultyArrowMenu difficultyArrowMenu;

    FontArrowMenu fontArrowMenu;
    SettingsMode mode;
    float menuScale = 2.0f;

    auto getMode(const SettingsMode& mode) -> void;

public:

    Settings();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    auto getFontSizeSlider() -> Slider&;
    auto getBaseSpeedSlider() -> Slider&;
    auto getWaveDelaySlider() -> Slider&;
    auto getPerWaveSlider() -> Slider&;
    auto getMaxWordLengthSlider() -> Slider&;
    auto getMinWordLengthSlider() -> Slider&;
    auto getFont() const -> std::string;

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
