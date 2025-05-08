#pragma once
#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable {
    sf::RectangleShape slider;
    sf::CircleShape dragger;

    float min;
    float max;
    float value;

    bool dragging = false;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Slider(float min, float max, float start, sf::Vector2f position, float width);

    auto handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window) -> void;

    auto getValue() const -> float;
    auto setValue(float val) -> void;
};

template <typename T>
requires std::is_arithmetic_v<T>
auto bound(T val, const T& min, const T& max) -> T;