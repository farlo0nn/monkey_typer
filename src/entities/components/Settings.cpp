//
// Created by Belinskiy Oleksandr on 09.05.2025.
//

#include "Settings.h"
#include <fstream>
#include <iostream>
#include "../../Constants.h"

Settings::Settings()
    : background_texture("assets/ui/menu/mainMenuBanner.png"),
      button_active_texture("assets/ui/menu/mainMenuButtonPressed.png"),
      button_inactive_texture("assets/ui/menu/mainMenuButton.png"),
      background(background_texture),
      font("assets/fonts/pixelify-sans.ttf"),
      characterSize(27),

      fontSizeSlider(20,48,24,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 100},300),
      fontSizeDisplay(font,"Font Size: ", 24),
      maxWordLengthSlider(2,7,7,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 20},300),
      maxWordLengthDisplay(font,"Max Length: ", 2),
      minWordLengthSlider(2,7,2,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 100},300),
      minWordLengthDisplay(font,"Min Length: ", 7),
      toMenu(button_active_texture, button_inactive_texture, font, "TO MENU", 24),
      systemSettings(button_active_texture, button_inactive_texture, font, "SYSTEM", 24),
      enemiesSettings(button_active_texture, button_inactive_texture, font, "ENEMIES", 24),
      difficultyArrowMenu({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 70}),
      fontArrowMenu({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 + 20})
{
    configure_component(background, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2}, 4.5);
    configure_component(toMenu, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2 + 150}, 1.6);
    configure_component(systemSettings, {WINDOW_SIZE.x/2 - 80, WINDOW_SIZE.y/2 - 200}, 0.8, 1.1);
    configure_component(enemiesSettings, {WINDOW_SIZE.x/2 + 80, WINDOW_SIZE.y/2 - 200}, 0.8, 1.1);
    systemSettings.onClick(
        [&]() {
            this->mode=SettingsMode::SYSTEM;
            enemiesSettings.click();
        }
    );
    enemiesSettings.onClick(
        [&]() {
            this->mode=SettingsMode::ENEMIES;
            systemSettings.click();
        }
    );
    systemSettings.click();
    fontSizeDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 150});
    fontSizeDisplay.setOutlineThickness(2);
    fontSizeDisplay.setCharacterSize(characterSize);
    maxWordLengthDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 70});
    maxWordLengthDisplay.setOutlineThickness(2);
    maxWordLengthDisplay.setCharacterSize(characterSize);
    minWordLengthDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 150});
    minWordLengthDisplay.setOutlineThickness(2);
    minWordLengthDisplay.setCharacterSize(characterSize);
    update();
}

template <typename T>
auto Settings::configure_component(T& component, sf::Vector2f position, float scalex, float scaley) -> void {
    component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
    component.setPosition(position);
    component.setScale({scalex, scaley});
}


template <typename T>
auto Settings::configure_component(T& component, sf::Vector2f position, float scale) -> void {
    Settings::configure_component(component, position, scale, scale);
}


void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw(background, states);

    switch (this->mode) {
        case SettingsMode::SYSTEM:
            target.draw(fontSizeSlider, states);
            target.draw(fontSizeDisplay, states);
            target.draw(difficultyArrowMenu, states);
            break;
        case SettingsMode::ENEMIES:
            target.draw(fontArrowMenu, states);
            target.draw(minWordLengthDisplay, states);
            target.draw(minWordLengthSlider, states);
            target.draw(maxWordLengthDisplay, states);
            target.draw(maxWordLengthSlider, states);
            break;
        default: break;
    }

    target.draw(toMenu, states);
    target.draw(systemSettings, states);
    target.draw(enemiesSettings, states);
}

auto Settings::getFontSizeSlider() -> Slider & {
    return fontSizeSlider;
}

auto Settings::update() -> void {
    fontSizeDisplay.setValue(fontSizeSlider.getValue());
    maxWordLengthDisplay.setValue(maxWordLengthSlider.getValue());
    minWordLengthDisplay.setValue(minWordLengthSlider.getValue());
}

auto Settings::getArrowMenus() -> std::vector<BaseArrowMenu*> {
    return {&difficultyArrowMenu, &fontArrowMenu};
}

auto Settings::getToMenu() -> Button &  { return toMenu; }

auto Settings::loadFromFile(const std::string& path) -> void {

    // LOADING LOGIC
    std::cout << "Loading " << path << "..." << std::endl;
    try {
        auto file = std::fstream(path);
        auto rawFontSize = std::string();
        file >> rawFontSize;
        auto fontSize = std::stoi(rawFontSize);

        auto difficulty = std::string();
        file >> difficulty;

        auto font = std::string();
        file >> font;

        auto rawMinLength = std::string();
        file >> rawMinLength;
        auto minLength = std::stoi(rawMinLength);

        auto rawMaxLength = std::string();
        file >> rawMaxLength;
        auto maxLength = std::stoi(rawMaxLength);

        fontSizeSlider.setValue(fontSize);
        fontSizeDisplay.setValue(fontSize);
        fontArrowMenu.setValue(font);
        difficultyArrowMenu.setValue(difficulty);
        minWordLengthSlider.setValue(minLength);
        maxWordLengthSlider.setValue(maxLength);

        std::cout << fontSize << " " << minLength << " " << maxLength << std::endl;

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

};

auto Settings::saveToFile(const std::string& path) const -> void {

    std::cout << "Saving settings to " << path << "..." << std::endl;
    std::cout << difficultyArrowMenu.getValue() << std::endl;
    try {
        auto file = std::fstream(path);
        file << fontSizeDisplay.getValue() << std::endl;
        file << difficultyArrowMenu.getValue() << std::endl;
        file << fontArrowMenu.getValue() << std::endl;
        file << minWordLengthDisplay.getValue() << std::endl;
        file << maxWordLengthDisplay.getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

auto Settings::set_mode(const SettingsMode &mode) -> void {
    this->mode = mode;
}

auto Settings::getEnemiesSettings() -> Button & {
    return enemiesSettings;
}

auto Settings::getSystemSettings() -> Button & {
    return systemSettings;
}

auto Settings::systemSettingsMode() -> bool {
    return mode == SettingsMode::SYSTEM;
}

auto Settings::getMaxWordLengthSlider() -> Slider & {
    return maxWordLengthSlider;
}

auto Settings::getMinWordLengthSlider() -> Slider & {
    return minWordLengthSlider;
}

auto Settings::valid() const -> std::pair<bool, std::optional<std::string>> {
    if (maxWordLengthDisplay.getValue() < minWordLengthDisplay.getValue()) {
        return {false, "Max length is less than min length"};
    }
    return {true, std::nullopt};
};

auto Settings::getDifficulty() const -> std::string {
    return difficultyArrowMenu.getValue();
}

auto Settings::getFont() const -> std::string {
    return fontArrowMenu.getValue();
}
