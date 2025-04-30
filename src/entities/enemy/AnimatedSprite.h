#pragma once
#include "SFML/Graphics/Sprite.hpp"

class AnimatedSprite : public sf::Sprite{
    int spriteFrameWidth;
    int spriteFrameHeight;
    int spriteFrameCount;
    float spriteFrameTime;
    int spriteCurrentFrame;
    float spriteElapsedTime;
public:
    AnimatedSprite(sf::Texture& texture, int frameCount, float frameTime);
    auto update(float deltaTime) -> void;
};
