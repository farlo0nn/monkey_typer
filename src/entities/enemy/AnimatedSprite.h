#pragma once
#include "Directions.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class AnimatedSprite : public sf::Sprite{
    int spriteFrameWidth;
    int spriteFrameHeight;
    int spriteFrameCount;
    float spriteFrameTime;
    int spriteCurrentFrame;
    float spriteElapsedTime;
    Directions texture_direction;
public:
    AnimatedSprite(sf::Texture& texture, int frameCount, float frameTime);
    AnimatedSprite(sf::Texture& texture, int frameCount);
    auto update(float deltaTime) -> void;
    auto setTextureDirection(Directions direction) -> void;
};

namespace as {

    enum class AnimatedSprites {
        BAT,
        BEE,
        BLUEBIRD,
        BUNNY,
        CHICKEN,
        DUCK,
        MUSHROOM,
        PIG,
        RADISH,
        RINO,
        SLIME,
        SNAIL,
        TRUNK,
        COUNT
    };

    struct DirectionInfo {
        std::string name;
        sf::Vector2f vector;
    };

    auto getAnimatedSprite(AnimatedSprites sprite, float frameTime) -> AnimatedSprite;
    auto getAnimatedSprite(AnimatedSprites sprite) -> AnimatedSprite;
}

