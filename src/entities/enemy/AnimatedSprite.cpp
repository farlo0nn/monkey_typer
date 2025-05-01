#include "AnimatedSprite.h"

#include <map>


AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount, float frameTime)
    : Sprite(texture), spriteFrameCount(frameCount), spriteFrameTime(frameTime) {
    spriteCurrentFrame = 0;
    spriteElapsedTime = 0.f;
    spriteFrameWidth = texture.getSize().x / spriteFrameCount;
    spriteFrameHeight = texture.getSize().y;
    setTextureRect(sf::IntRect({spriteCurrentFrame * spriteFrameWidth, 0}, {spriteFrameWidth, spriteFrameHeight}));
}

AnimatedSprite::AnimatedSprite(sf::Texture& texture, int frameCount) :
Sprite(texture), spriteFrameCount(frameCount), spriteFrameTime(0.2f) {
    AnimatedSprite(texture, frameCount, frameCount);
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