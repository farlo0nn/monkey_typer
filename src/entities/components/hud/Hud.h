#pragma once

#include <SFML/Graphics.hpp>
#include "../displays/MetricDisplay.h"

class Hud : public sf::Drawable {
protected:
    sf::Texture background_texture;
    sf::Font font;
    int fontSize;
    sf::Sprite background;
    MetricDisplay<float> wpm;
    MetricDisplay<int> score;
    MetricDisplay<int> highestScore;
    MetricDisplay<int> round;


    template<typename  T>
    static auto configureComponent(T &component, sf::Vector2f position, float scalex, float scaley) -> void;

    auto scale(sf::Vector2f scale) -> void;
    auto setPosition(sf::Vector2f position) -> void;


public:
    Hud(const sf::Vector2f& position);

    auto setScore(int score) -> void;
    auto setHighestScore(int highestScore) -> void;
    auto setWPM(float wpm) -> void;
    auto setRound(int round) -> void;

    auto getHighestScore() const -> int;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
