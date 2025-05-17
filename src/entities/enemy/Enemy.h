#pragma once

#include "spawn/EnemyState.h"
#include "../../logic/word/Word.h"
#include "label/HighlightedLabel.h"
#include <SFML/Graphics.hpp>

#include "sprite/AnimatedSprite.h"

enum class Enemies {
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


class Enemy : public sf::Drawable {
public:

    Enemy(const EnemyState &state, Enemies enemyType, const Word &word, const sf::Font &font,
          unsigned int fontsize, int base_speed);

    auto update(int round, float deltaTime) -> void;
    auto typeNextChar() -> void;
    auto resetTyping() -> void;
    auto collides(const sf::Sprite& other) const -> bool;

    auto getEnemyState() const -> EnemyState;
    auto getSprite() const -> const AnimatedSprite&;
    auto getWord() const -> const Word&;
    auto getTypingIndex() const -> int;
    auto getCurrentExpectedChar() const -> char;

    auto isActive() const -> bool;
    auto isWordTyped() const -> bool;

    auto setPosition(const sf::Vector2f& pos) -> void;
    auto setActive(bool active) -> void;

    auto operator==(const Enemy& other) const -> bool;

private:
    EnemyState state;
    std::optional<AnimatedSprite> sprite;
    std::shared_ptr<sf::Texture> texture;
    HighlightedLabel label;
    Word word;
    size_t typing_index;
    bool active_target;
    int base_speed;

    auto updateLabelPosition() -> void;
    auto getFrameCount(const Enemies enemyType) -> int;

    static auto getPath(Enemies sprite) -> std::string;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite.value(), states);
        target.draw(label, states);
    }
};
