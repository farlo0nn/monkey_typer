#include "HighlighedLabel.h"

HighlighedLabel::HighlighedLabel(const sf::Font& font, unsigned int fontsize)
    : typingIndex(0), typedText(font), untypedText(font)
{
    setFont(font);
    setCharacterSize(fontsize);
    typedText.setFont(font);
    untypedText.setFont(font);
    typedText.setFillColor(sf::Color::Red);
    untypedText.setFillColor(sf::Color::Green);
    typedText.setOutlineColor(sf::Color::Black);
    untypedText.setOutlineColor(sf::Color::Black);
    typedText.setOutlineThickness(3);
    untypedText.setOutlineThickness(3);
}

void HighlighedLabel::setString(const std::string& str) {
    fullString = str;
    updateHighlight();
}

void HighlighedLabel::setFont(const sf::Font& font) {
    typedText.setFont(font);
    untypedText.setFont(font);
}

void HighlighedLabel::setPosition(const sf::Vector2f& pos) {
    typedText.setPosition(pos);
    updateHighlight();
}

void HighlighedLabel::setCharacterSize(unsigned int size) {
    typedText.setCharacterSize(size);
    untypedText.setCharacterSize(size);
    updateHighlight();
}

void HighlighedLabel::setTypingIndex(size_t index) {
    typingIndex = index;
    updateHighlight();
}

void HighlighedLabel::setColors(sf::Color typed, sf::Color untyped) {
    typedColor = typed;
    untypedColor = untyped;
    updateHighlight();
}

void HighlighedLabel::updateHighlight() {
    std::string typedStr = fullString.substr(0, typingIndex);
    std::string untypedStr = fullString.substr(typingIndex);

    typedText.setString(typedStr);
    untypedText.setString(untypedStr);

    typedText.setFillColor(typedColor);
    untypedText.setFillColor(untypedColor);

    // Position untyped part after typed part
    auto typedBounds = typedText.getGlobalBounds();
    sf::Vector2f offset(typedBounds.position.x + typedBounds.size.x, typedText.getPosition().y);
    untypedText.setPosition(offset);
}

auto HighlighedLabel::getGlobalBounds() const -> sf::FloatRect {
    auto a = typedText.getGlobalBounds();
    auto b = untypedText.getGlobalBounds();
    return sf::FloatRect(
        {a.position.x, a.position.y},
        {(b.position.x + b.size.x) - a.position.x, std::max(a.size.y, b.size.y)}
    );
}

auto HighlighedLabel::getLocalBounds() const -> sf::FloatRect {
    auto g = getGlobalBounds();
    return sf::FloatRect(
        {0,0},
        {g.size.x,g.size.y}
    );
}

void HighlighedLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(typedText, states);
    target.draw(untypedText, states);
}
