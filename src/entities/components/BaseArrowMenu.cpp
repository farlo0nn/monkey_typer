//
// Created by Belinskiy Oleksandr on 09.05.2025.
//

#include "BaseArrowMenu.h"

#include <iostream>

BaseArrowMenu::BaseArrowMenu(const sf::Vector2f& position, const std::vector<std::string>& values) :
    values(values),
    font("assets/fonts/pixelify-sans.ttf"),
    leftArrowActive("assets/ui/settings/minus.png"),
    leftArrowInactive("assets/ui/settings/minus_pressed.png"),
    rightArrowActive("assets/ui/settings/plus_pressed.png"),
    rightArrowInactive("assets/ui/settings/plus_pressed.png"),
    leftArrow(leftArrowInactive, leftArrowActive),
    rightArrow(rightArrowInactive, rightArrowActive),
    valueLabel(font)
{
    leftArrow.setPosition(position);
    auto valueLabelBounds = leftArrow.getLocalBounds();
    valueLabel.setOrigin({valueLabelBounds.size.x/2, valueLabelBounds.size.y/2});
    valueLabel.setPosition({position.x+leftArrow.getLocalBounds().size.x + 70, position.y + valueLabelBounds.size.y/2 + 10});
    rightArrow.setPosition({position.x+leftArrow.getLocalBounds().size.x + 170, position.y});
    valueLabel.setString(values[0]);

    valueLabel.setOutlineColor(sf::Color::Black);
    valueLabel.setOutlineThickness(2);
    leftArrow.onClick([this]() {
        setLeftValue();
    });

    rightArrow.onClick([this]() {
        setRightValue();
    });
}

void BaseArrowMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(leftArrow, states);
    target.draw(valueLabel, states);
    target.draw(rightArrow, states);
}

auto BaseArrowMenu::setLeftValue() -> void {
    if (curValId - 1 >= 0) {
        curValId--;
        valueLabel.setString(values[curValId]);
    }
}

auto BaseArrowMenu::setRightValue() -> void {
    if (curValId + 1 < values.size()) {
        curValId++;
        valueLabel.setString(values[curValId]);
    }
}

