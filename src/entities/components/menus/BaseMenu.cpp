#include "BaseMenu.h"

#include "../../../Constants.h"

BaseMenu::BaseMenu()
    : background_texture("assets/ui/menu/mainMenuBanner.png"),
      button_active_texture("assets/ui/menu/mainMenuButtonPressed.png"),
      button_inactive_texture("assets/ui/menu/mainMenuButton.png"),
      background(background_texture),
      font("assets/fonts/pixelify-sans.ttf"),
      fontSize(48)
{
    configure_component(background, {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2}, 4.5);
}

auto BaseMenu::get_buttons() -> std::vector<Button>& {
    return buttons;
}


template <typename T>
auto BaseMenu::configure_component(T& component, sf::Vector2f position, float scale) -> void {
    component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
    component.setPosition(position);
    component.setScale({scale, scale});
}


auto BaseMenu::create_button(const std::string &text, const sf::Font& font, sf::Vector2f position) -> Button {
    auto button = Button(button_active_texture, button_inactive_texture, font, text, 24);
    configure_component(button, position, menuScale);
    return button;
}

auto BaseMenu::create_button(const std::string &text, sf::Vector2f position) -> Button {
    auto button = Button(button_active_texture, button_inactive_texture, font, text, 24);
    configure_component(button, position, menuScale);
    return button;
}


void BaseMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    for (const auto& button : buttons) {
        target.draw(button, states);
    }
}




