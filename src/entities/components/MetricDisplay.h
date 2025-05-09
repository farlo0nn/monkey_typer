#pragma once
#include "SFML/Graphics.hpp"
#include <type_traits>
#include <iomanip>
#include <sstream>
#include <string>


inline auto to_str_with_precision(float value, int precision) -> std::string {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}


template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class MetricDisplay : public sf::Drawable{
    sf::Font font;
    sf::Text nameLabel;
    sf::Text valueLabel;
    T value;

public:
    MetricDisplay(const sf::Font &font, const std::string &name, const T& value);
    auto getValue() const -> T;
    auto setValue(const T& value) -> void;
    auto updateLabel() -> void;
    auto setPosition(const sf::Vector2f& position) -> void;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#pragma once
#include "MetricDisplay.h"

template <Arithmetic T>
MetricDisplay<T>::MetricDisplay(const sf::Font &font, const std::string &name, const T& value) : font(font), nameLabel(font, name), valueLabel(font) {
    valueLabel.setString(std::to_string(value));
}

template <Arithmetic T>
void MetricDisplay<T>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(nameLabel, states);
    target.draw(valueLabel, states);
}

template <Arithmetic T>
auto MetricDisplay<T>::getValue() const -> T {
    return this->value;
}

template <Arithmetic T>
auto MetricDisplay<T>::setPosition(const sf::Vector2f& position) -> void {
    nameLabel.setPosition(position);
    valueLabel.setPosition({position.x + nameLabel.getLocalBounds().size.x + 20, position.y});
}

template <Arithmetic T>
auto MetricDisplay<T>::setValue(const T& value) -> void {
    this->value = value;
    updateLabel();
}

template <Arithmetic T>
auto MetricDisplay<T>::updateLabel() -> void {
    this->valueLabel.setString(to_str_with_precision(this->value, 1));
}

template <>
inline auto MetricDisplay<int>::updateLabel() -> void {
    this->valueLabel.setString(std::to_string(this->value));
}

