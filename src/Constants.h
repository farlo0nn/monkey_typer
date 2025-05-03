#pragma once

#include <SFML/Graphics.hpp>

constexpr auto FONT_PATH = "assets/fonts/pixelify-sans.ttf";
constexpr auto WORDS_PATH = "assets/words.txt";
constexpr auto WINDOW_SIZE = sf::Vector2u(1080, 720);
constexpr auto CENTER_POSITION = sf::Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
constexpr auto BASE_SPEED = 30;
constexpr auto WORD_FONTSIZE = 24;
