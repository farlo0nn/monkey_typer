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

    // Enemy(const EnemyState &state, const std::string& texture_path, const AnimatedSprite &sprite,  const Word& word, const sf::Font& font, unsigned int fontsize, int base_speed);

    Enemy(const EnemyState &state, Enemies enemyType, const Word &word, const sf::Font &font,
          unsigned int fontsize, int base_speed);

    auto update(int round, float deltaTime) -> void;

    auto get_enemy_state() const -> EnemyState;
    auto get_sprite() const -> const AnimatedSprite&;

    auto set_position(const sf::Vector2f& pos) -> void;
    auto get_word() const -> const Word&;
    auto get_typing_index() const -> int;
    auto type_next_char() -> void;
    auto get_current_expected_char() const -> char;
    auto is_active() const -> bool;
    auto is_word_typed() const -> bool;
    auto set_active(bool active) -> void;
    auto reset_typing() -> void;
    auto collides(const sf::Sprite& other) const -> bool;
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

    auto update_label_position() -> void;
    auto getFrameCount(const Enemies enemyType) -> int;

    static auto getPath(Enemies sprite) -> std::string;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite.value(), states);
        target.draw(label, states);
    }
};

static sf::Texture& dummyTexture() {
    static sf::Texture dummy = sf::Texture();
    return dummy;
}
