
#pragma once  
#include "../spawn/Directions.h"  
#include "SFML/Graphics/Sprite.hpp"  
#include "SFML/Graphics/Texture.hpp"  
  
class AnimatedSprite : public sf::Sprite {  
    int frameWidth;  
    int frameHeight;  
    int frameCount;  
    float frameTime;  
    int currentFrame;  
    float elapsedTime;  
    Directions texture_direction;  
public:  
    AnimatedSprite(const sf::Texture& texture, int frameCount, float frameTime);  
    AnimatedSprite(sf::Texture& texture, int frameCount);  
    AnimatedSprite(sf::Texture& texture);  
  
    auto update(float deltaTime) -> void;  
    auto setTextureDirection(Directions direction) -> void;  
};