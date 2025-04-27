#include <SFML/Graphics.hpp>
#include <string>

inline const std::string FONT_PATH = "assets/fonts/arial.ttf";
inline const std::string WORDS_PATH = "assets/words.txt";
constexpr auto WINDOW_SIZE = sf::Vector2u(700, 700);
constexpr auto CENTER_POSITION = sf::Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
constexpr auto BASE_SPEED = 30;