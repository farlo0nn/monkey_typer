#pragma once

#pragma once
#include "../buttons/Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

class BaseMenu : public sf::Drawable {
protected:
    sf::Texture background_texture;
    sf::Texture button_active_texture;
    sf::Texture button_inactive_texture;
    sf::Font font;
    int fontSize;
    sf::Sprite background;
    std::vector<Button> buttons;

    float menuScale = 2.0f;

    template<typename  T>
    static auto configure_component(T &component, sf::Vector2f position, float scale) -> void;

    auto create_button(const std::string &text, const sf::Font &font, sf::Vector2f position) -> Button;
    auto create_button(const std::string &text, sf::Vector2f position) -> Button;

public:

    BaseMenu();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<Button>& get_buttons();


};
