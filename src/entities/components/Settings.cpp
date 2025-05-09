//
// Created by Belinskiy Oleksandr on 09.05.2025.
//

#include "Settings.h"

#include <iostream>

#include "../../Constants.h"

Settings::Settings()
    : background_texture("assets/ui/menu/mainMenuBanner.png"),
      button_active_texture("assets/ui/menu/mainMenuButtonPressed.png"),
      button_inactive_texture("assets/ui/menu/mainMenuButton.png"),
      background(background_texture),
      font("assets/fonts/pixelify-sans.ttf"),
      characterSize(32),
      fontSizeSlider(20,48,24,{WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 150},300),
      fontSizeDisplay(font,"Font Size: ", 24),
      toMenu(button_inactive_texture, button_active_texture, font, "TO MENU", characterSize),
      difficultyArrowMenu({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 90}),
      fontArrowMenu({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2})
{
    configure_component(background, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2}, 4.5);
    fontSizeDisplay.setPosition({WINDOW_SIZE.x/2 - 140, WINDOW_SIZE.y/2 - 210});
    fontSizeDisplay.setOutlineThickness(2);
    fontSizeDisplay.setCharacterSize(characterSize);

}


template <typename T>
auto Settings::configure_component(T& component, sf::Vector2f position, float scale) -> void {
    component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
    component.setPosition(position);
    component.setScale({scale, scale});
}


void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(fontSizeSlider, states);
    target.draw(fontSizeDisplay, states);
    target.draw(difficultyArrowMenu, states);
    target.draw(fontArrowMenu, states);
}

auto Settings::getFontSizeSlider() -> Slider & {
    return fontSizeSlider;
}

auto Settings::update() -> void {
    fontSizeDisplay.setValue(fontSizeSlider.getValue());
}


