#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include "Button.h"


class BaseArrowMenu : public sf::Drawable{
protected:
    std::vector<std::string> values;
    int curValId;
    sf::Font font;
    sf::Text valueLabel;
    sf::Texture leftArrowActive;
    sf::Texture rightArrowActive;
    sf::Texture leftArrowInactive;
    sf::Texture rightArrowInactive;
    Button leftArrow;
    Button rightArrow;

    auto setLeftValue() -> void;
    auto setRightValue() -> void;

public:
    BaseArrowMenu(const sf::Vector2f &position, const std::vector<std::string> &values);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    auto getLeftArrow() -> Button&;
    auto getRightArrow() -> Button&;
};
