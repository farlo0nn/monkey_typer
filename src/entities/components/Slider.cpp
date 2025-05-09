#include "Slider.h"

Slider::Slider(const float min, const float max, float start, sf::Vector2f position, float width)
    : min(min), max(max), value(start) {

    slider.setSize({width, 5});
    slider.setFillColor(sf::Color(196, 164, 132));
    slider.setOutlineColor(sf::Color(110, 38, 14));
    slider.setOutlineThickness(3);
    slider.setPosition(position);

    dragger.setPointCount(200);
    dragger.setRadius(12);
    dragger.setFillColor(sf::Color(149, 69, 53));
    dragger.setOutlineThickness(3);
    dragger.setOutlineColor(sf::Color(110, 38, 14));
    dragger.setOrigin({dragger.getRadius(), dragger.getRadius()});


    auto x = position.x + ((value - min) / (max - min)) * width;
    dragger.setPosition({x, position.y + 2.5f});
}


void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(slider, states);
    target.draw(dragger, states);
}

auto Slider::handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window) -> void {
    auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    if (event->is<sf::Event::MouseButtonPressed>()  && dragger.getGlobalBounds().contains(mousePos)) {
        dragging = true;
    }

    if (event->is<sf::Event::MouseButtonReleased>()) {
        dragging = false;
    }

    if (dragging && event->is<sf::Event::MouseMoved>()) {
        auto left = slider.getPosition().x;
        auto right = left + slider.getSize().x;

        float x = bound(mousePos.x, left, right);
        dragger.setPosition({x, dragger.getPosition().y});

        auto t = (x - left) / (right - left);
        value = min + t * (max - min);
    }
}

float Slider::getValue() const {
    return value;
}

void Slider::setValue(float val) {

    value = bound(val, min, max);

    auto x = slider.getPosition().x + ((value - min) / (max - min)) * slider.getSize().x;
    dragger.setPosition({x, slider.getPosition().y + 2.5f});
}


template <typename T>
requires std::is_arithmetic_v<T>
auto bound(T val, const T& min, const T& max) -> T {
    if (val > max) {
        val = max;
    } else if (val < min) {
        val = min;
    }
    return val;
}
