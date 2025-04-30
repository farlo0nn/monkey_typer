
#include "AnimatedSprite.h"

#include <iostream>
#include <ostream>

#include "SFML/Graphics/Texture.hpp"


AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount, float frameTime)
    : Sprite(texture), spriteFrameCount(frameCount), spriteFrameTime(frameTime) {
    spriteCurrentFrame = 0;
    spriteElapsedTime = 0.f;
    spriteFrameWidth = texture.getSize().x / spriteFrameCount;
    spriteFrameHeight = texture.getSize().y;
    setTextureRect(sf::IntRect({spriteCurrentFrame * spriteFrameWidth, 0}, {spriteFrameWidth, spriteFrameHeight}));
}

auto AnimatedSprite::update(float deltaTime) -> void {
    spriteElapsedTime += deltaTime;
    if (spriteElapsedTime >= spriteFrameTime) {
        spriteElapsedTime = 0.f;
        spriteCurrentFrame = (spriteCurrentFrame + 1) % spriteFrameCount;
        setTextureRect(sf::IntRect({spriteCurrentFrame * spriteFrameWidth, 0}, {spriteFrameWidth, spriteFrameHeight}));
    }
}

