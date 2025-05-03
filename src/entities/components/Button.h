#pragma once
#include "SFML/Graphics.hpp"

using Callback = std::function<void()>;

class Button : public sf::Drawable{
    sf::Sprite sprite;
    sf::Texture textureActive;
    sf::Texture textureInactive;

    bool clicked = false;
    bool active = false;
    Callback callback;


    auto setActive(bool active) -> void;

public:

    Button(const sf::Texture& textureInactive, const sf::Texture& textureActive);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

    auto getPosition() -> sf::Vector2f;
    auto setPosition(const sf::Vector2f& position) -> void;
    auto getGlobalBounds() -> sf::FloatRect;
    auto isClicked() -> bool;
    auto onClick(Callback cb) -> void;
    auto click() -> void;
};
