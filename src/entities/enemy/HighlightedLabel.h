#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class HighlightedLabel : public sf::Drawable {
public:
    HighlightedLabel(const sf::Font& font, unsigned int fontsize);

    void setString(const std::string& str);
    void setFont(const sf::Font& font);
    void setPosition(const sf::Vector2f& pos);
    void setTypingIndex(size_t index);
    void setCharacterSize(unsigned int size);
    void setColors(sf::Color typed, sf::Color untyped);
    auto reset() -> void;
    auto getGlobalBounds() const -> sf::FloatRect;
    auto getLocalBounds() const -> sf::FloatRect;

private:
    sf::Text typedText;
    sf::Text untypedText;
    std::string fullString;
    size_t typingIndex;
    sf::Color typedColor = sf::Color::Green;
    sf::Color untypedColor = sf::Color::White;

    void updateHighlight();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
