#include "AnimatedSprite.h"

#include <iostream>
#include <map>


AnimatedSprite::AnimatedSprite(const sf::Texture& texture, int frameCount, float frameTime)
    : Sprite(texture), frameCount(frameCount), frameTime(frameTime)
{
    currentFrame = 0;
    elapsedTime = 0.f;
    frameWidth = texture.getSize().x / frameCount;
    frameHeight = texture.getSize().y;
    setTextureRect(sf::IntRect({currentFrame * frameWidth, 0}, {frameWidth, frameHeight}));
}

auto AnimatedSprite::setTextureDirection(Directions direction) -> void {
    texture_direction = direction;
    if (texture_direction == Directions::LEFT) {
        setOrigin({getLocalBounds().size.x, 0});
        scale({-1,1});
    }
}

AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount)
    :  AnimatedSprite(texture, frameCount, 0.1f) {}

AnimatedSprite::AnimatedSprite(sf::Texture& texture) : AnimatedSprite(texture, 1) {}

auto AnimatedSprite::update(float deltaTime) -> void {
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;
        setTextureRect(sf::IntRect({currentFrame * frameWidth, 0}, {frameWidth, frameHeight}));
    }

}
