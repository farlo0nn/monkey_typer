#include "AnimatedSprite.h"

#include <map>


AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount, float frameTime)
    : Sprite(texture), spriteFrameCount(frameCount), spriteFrameTime(frameTime),  texture_direction(Directions::RIGHT){
    spriteCurrentFrame = 0;
    spriteElapsedTime = 0.f;
    spriteFrameWidth = texture.getSize().x / spriteFrameCount;
    spriteFrameHeight = texture.getSize().y;

    setTextureRect(sf::IntRect({spriteCurrentFrame * spriteFrameWidth, 0}, {spriteFrameWidth, spriteFrameHeight}));

    if (texture_direction == Directions::LEFT) {
        setOrigin({getLocalBounds().size.x, 0});
        scale({-1,1});
    }
}

auto AnimatedSprite::setTextureDirection(Directions directions) -> void {
    texture_direction = directions;
    if (texture_direction == Directions::LEFT) {
        setOrigin({getLocalBounds().size.x, 0});
        scale({-1,1});
    }
}

AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount)
    : Sprite(texture)
{
    AnimatedSprite(texture, frameCount, 0.1f);
}

auto AnimatedSprite::update(float deltaTime) -> void {
    spriteElapsedTime += deltaTime;
    if (spriteElapsedTime >= spriteFrameTime) {
        spriteElapsedTime = 0.f;
        spriteCurrentFrame = (spriteCurrentFrame + 1) % spriteFrameCount;
        setTextureRect(sf::IntRect({spriteCurrentFrame * spriteFrameWidth, 0}, {spriteFrameWidth, spriteFrameHeight}));
    }

}




namespace as {

    static std::map<AnimatedSprites, sf::Texture> textures;

    sf::Texture& getTexture(AnimatedSprites sprite) {
        auto it = textures.find(sprite);
        if (sprite != AnimatedSprites::COUNT && it != textures.end())
            return it->second;

        std::string path;
        switch (sprite) {
            case AnimatedSprites::CHICKEN: path = "assets/sprites/enemies/chicken.png"; break;
            case AnimatedSprites::RADISH: path = "assets/sprites/enemies/radish.png"; break;
            case AnimatedSprites::BAT: path = "assets/sprites/enemies/bat.png"; break;
            case AnimatedSprites::BEE: path = "assets/sprites/enemies/bee.png"; break;
            case AnimatedSprites::PIG: path = "assets/sprites/enemies/pig.png"; break;
            case AnimatedSprites::DUCK: path = "assets/sprites/enemies/duck.png"; break;
            case AnimatedSprites::RINO: path = "assets/sprites/enemies/rino.png"; break;
            case AnimatedSprites::BUNNY: path = "assets/sprites/enemies/bunny.png"; break;
            case AnimatedSprites::SLIME: path = "assets/sprites/enemies/slime.png"; break;
            case AnimatedSprites::SNAIL: path = "assets/sprites/enemies/snail.png"; break;
            case AnimatedSprites::TRUNK: path = "assets/sprites/enemies/trunk.png"; break;
            case AnimatedSprites::BLUEBIRD: path = "assets/sprites/enemies/bluebird.png"; break;
            case AnimatedSprites::MUSHROOM: path = "assets/sprites/enemies/mushroom.png"; break;
            case AnimatedSprites::COUNT: break;
            default: throw std::invalid_argument("Invalid sprite");
        }

        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);

        return textures.emplace(sprite, std::move(texture)).first->second;;
    }

    auto getAnimatedSprite(AnimatedSprites sprite, float frameTime) -> AnimatedSprite {
        auto frameCount = int();

        switch (sprite) {
            case AnimatedSprites::CHICKEN: {
                frameCount = 14;
            }; break;
            case AnimatedSprites::RADISH: {
                frameCount = 12;
            }; break;
            case AnimatedSprites::BAT: {
                frameCount = 7;
            }; break;
            case AnimatedSprites::BEE: {
                frameCount = 6;
            }; break;
            case AnimatedSprites::PIG: {
                frameCount = 16;
            }; break;
            case AnimatedSprites::TRUNK: {
                frameCount = 14;
            }; break;
            case AnimatedSprites::DUCK: {
                frameCount = 10;
            }; break;
            case AnimatedSprites::RINO: {
                frameCount = 6;
            }; break;
            case AnimatedSprites::BUNNY: {
                frameCount = 12;
            }; break;
            case AnimatedSprites::SLIME: {
                frameCount = 10;
            }; break;
            case AnimatedSprites::SNAIL: {
                frameCount = 10;
            }; break;
            case AnimatedSprites::BLUEBIRD: {
                frameCount = 9;
            }; break;
            case AnimatedSprites::MUSHROOM: {
                frameCount = 16;
            }; break;

            case AnimatedSprites::COUNT: break;
            default: throw std::invalid_argument("Unknown Direction");
        }
        return AnimatedSprite(
            getTexture(sprite),
            frameCount,
            frameTime
        );
    }

    auto getAnimatedSprite(AnimatedSprites sprite) -> AnimatedSprite {
        return getAnimatedSprite(sprite, 0.1f);
    }
}