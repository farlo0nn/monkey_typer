#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

using Callback = std::function<void()>;

class Button : public sf::Drawable {
    sf::Sprite sprite;
    sf::Texture textureActive;
    sf::Texture textureInactive;

    std::optional<sf::Text> label;

    bool clicked = false;
    bool active = false;
    Callback callback;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateLabelPosition();

public:
    Button(const sf::Texture& textureInactive, const sf::Texture& textureActive, const sf::Font& font, const std::string& text, int fontSize);
    Button(const sf::Texture& textureInactive, const sf::Texture& textureActive);


    auto setPosition(sf::Vector2f pos) -> void;
    auto setScale(sf::Vector2f scale) -> void;
    auto setOrigin(sf::Vector2f origin) -> void;
    auto setActive(bool active) -> void;

    auto getGlobalBounds() -> sf::FloatRect;
    auto getLocalBounds() -> sf::FloatRect;

    auto isClicked() const -> bool;

    void onClick(Callback cb);
    void click();

    bool contains(sf::Vector2f point) const;
};
