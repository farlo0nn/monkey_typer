#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct Word {
    char first_letter;
    std::string value;
    sf::Vector2f position;

    auto size() -> int;
};