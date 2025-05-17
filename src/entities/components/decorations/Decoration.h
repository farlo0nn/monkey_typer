#pragma once
#include "../../enemy/sprite/AnimatedSprite.h"

class Decoration {
public:
    static auto getDecorationParams() -> std::vector<std::pair<sf::Vector2f, float>>;
};
