//
// Created by Belinskiy Oleksandr on 09.05.2025.
//

#include "Settings.h"
#include <fstream>
#include <iostream>

#include "../utils/utils.h"
#include "../../../Constants.h"

Settings::Settings()
    : background_texture("assets/ui/menu/mainMenuBanner.png"),
      button_active_texture("assets/ui/menu/mainMenuButtonPressed.png"),
      button_inactive_texture("assets/ui/menu/mainMenuButton.png"),
      background(background_texture),
      font("assets/fonts/pixelify-sans.ttf"),
      characterSize(27),

      fontSizeSlider(20,48,24,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 100},300),
      fontSizeDisplay(font,"Font Size:", 24),
      maxWordLengthSlider(2,10,10,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 20},300),
      maxWordLengthDisplay(font,"Max Length:", 10),
      minWordLengthSlider(2,10,2,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 100},300),
      minWordLengthDisplay(font,"Min Length:", 2),
      baseSpeedSlider(60, 120, 60,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 100},300),
      baseSpeedDisplay(font,"Base Speed:", 60),
      waveDelaySlider(2,7,4,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 20},300),
      waveDelayDisplay(font,"Wave delay:", 4),
      perWaveSlider(2,6,3,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 + 60},300),
      perWaveDisplay(font,"SpawnPer wave:", 3),

      toMenu(button_active_texture, button_inactive_texture, font, "TO MENU", 24),
      systemSettings(button_active_texture, button_inactive_texture, font, "SYSTEM", 24),
      enemiesSettings(button_active_texture, button_inactive_texture, font, "ENEMY", 24),
      fontArrowMenu({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 + 20})
{
    utils::configureComponent(background, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2}, 4.5);
    utils::configureComponent(toMenu, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2 + 150}, 1.6);
    utils::configureComponent(systemSettings, {WINDOW_SIZE.x/2 - 80, WINDOW_SIZE.y/2 - 200}, 0.8, 1.1);
    utils::configureComponent(enemiesSettings, {WINDOW_SIZE.x/2 + 80, WINDOW_SIZE.y/2 - 200}, 0.8, 1.1);
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

    maxWordLengthDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 70});
    maxWordLengthDisplay.setOutlineThickness(2);
    maxWordLengthDisplay.setCharacterSize(characterSize);
    minWordLengthDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 150});
    minWordLengthDisplay.setOutlineThickness(2);
    minWordLengthDisplay.setCharacterSize(characterSize);

    baseSpeedDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 150});
    baseSpeedDisplay.setOutlineThickness(2);
    baseSpeedDisplay.setCharacterSize(characterSize);

    waveDelayDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 70});
    waveDelayDisplay.setOutlineThickness(2);
    waveDelayDisplay.setCharacterSize(characterSize);

    perWaveDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 + 10});
    perWaveDisplay.setOutlineThickness(2);
    perWaveDisplay.setCharacterSize(characterSize);


    update();
}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw(background, states);

    switch (this->mode) {
        case SettingsMode::SYSTEM:
            target.draw(baseSpeedDisplay, states);
            target.draw(baseSpeedSlider, states);
            target.draw(waveDelayDisplay, states);
            target.draw(waveDelaySlider, states);
            target.draw(perWaveDisplay, states);
            target.draw(perWaveSlider, states);
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
    baseSpeedDisplay.setValue(baseSpeedSlider.getValue());
    perWaveDisplay.setValue(perWaveSlider.getValue());
    waveDelayDisplay.setValue(waveDelaySlider.getValue());
}

auto Settings::getArrowMenus() -> std::vector<BaseArrowMenu*> {
    return {&fontArrowMenu};
}

auto Settings::getToMenu() -> Button &  { return toMenu; }

auto Settings::loadFromFile(const std::string& path) -> void {

    // LOADING LOGIC
    std::cout << "Loading " << path << "..." << std::endl;
    try {
        auto file = std::fstream(path);

        auto baseSpeedRaw = std::string();
        auto waveDelayRaw = std::string();
        auto perWaveRaw = std::string();
        file >> baseSpeedRaw;
        file >> waveDelayRaw;
        file >> perWaveRaw;

        auto baseSpeed = std::stoi(baseSpeedRaw);
        auto waveDelay = std::stoi(waveDelayRaw);
        auto perWave = std::stoi(perWaveRaw);

        auto font = std::string();
        file >> font;

        auto rawMinLength = std::string();
        file >> rawMinLength;
        auto minLength = std::stoi(rawMinLength);

        auto rawMaxLength = std::string();
        file >> rawMaxLength;
        auto maxLength = std::stoi(rawMaxLength);

        baseSpeedSlider.setValue(baseSpeed);
        baseSpeedDisplay.setValue(baseSpeed);
        waveDelaySlider.setValue(waveDelay);
        waveDelayDisplay.setValue(waveDelay);
        perWaveSlider.setValue(perWave);
        perWaveDisplay.setValue(perWave);

        fontArrowMenu.setValue(font);
        minWordLengthSlider.setValue(minLength);
        maxWordLengthSlider.setValue(maxLength);

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

};

auto Settings::saveToFile(const std::string& path) const -> void {

    std::cout << "Saving settings to " << path << "..." << std::endl;

    try {
        auto file = std::fstream(path);
        file << baseSpeedDisplay.getValue() << std::endl;
        file << waveDelayDisplay.getValue() << std::endl;
        file << perWaveDisplay.getValue() << std::endl;
        file << fontArrowMenu.getValue() << std::endl;
        file << minWordLengthDisplay.getValue() << std::endl;
        file << maxWordLengthDisplay.getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

auto Settings::getMode(const SettingsMode &mode) -> void {
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

auto Settings::getBaseSpeedSlider() -> Slider& {
    return baseSpeedSlider;
}

auto Settings::getWaveDelaySlider() -> Slider& {
    return waveDelaySlider;
}

auto Settings::getPerWaveSlider() -> Slider& {
    return perWaveSlider;
}

auto Settings::valid() const -> std::pair<bool, std::optional<std::string>> {
    if (maxWordLengthDisplay.getValue() < minWordLengthDisplay.getValue()) {
        return {false, "Max length is less than min length"};
    }
    return {true, std::nullopt};
};

auto Settings::getFont() const -> std::string {
    return fontArrowMenu.getValue();
}
