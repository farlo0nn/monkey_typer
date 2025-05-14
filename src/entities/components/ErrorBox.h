#pragma once
#include <SFML/Graphics.hpp>


class ErrorBox : public sf::Drawable {
    sf::Font font;
    sf::Text message;
    sf::Texture backgroundTexture;;
    sf::Sprite background;
public:
    ErrorBox(const sf::Font& font, const std::string& message);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    auto setPosition(sf::Vector2f position) -> void;
    auto setMessage(const std::string& message) -> void;
};