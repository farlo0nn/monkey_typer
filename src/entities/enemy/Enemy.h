#pragma once

#include "spawn/EnemyState.h"
#include "../../logic/word/Word.h"
#include "label/HighlightedLabel.h"
#include <SFML/Graphics.hpp>

#include "sprite/AnimatedSprite.h"

class Enemy : public sf::Drawable {
public:

    Enemy(const EnemyState &state, const AnimatedSprite &sprite,  const Word& word, const sf::Font& font, unsigned int fontsize, int base_speed);

    auto update(int round, float deltaTime) -> void;

    auto get_enemy_state() const -> EnemyState;
    auto get_sprite() const -> const AnimatedSprite&;

    auto set_position(const sf::Vector2f& pos) -> void;
    auto get_word() const -> const Word&;
    auto get_typing_index() const -> int;
    auto type_next_char() -> void;
    auto get_current_expected_char() const -> char;
    auto is_active() const -> bool;
    auto is_word_typed() -> bool;
    auto set_active(bool active) -> void;
    auto reset_typing() -> void;
    auto collides(sf::Sprite& other) const -> bool;
    auto operator==(const Enemy& other) const -> bool;

private:
    EnemyState state;
    AnimatedSprite sprite;
    sf::Texture texture;
    HighlightedLabel label;
    Word word;
    size_t typing_index;
    bool active_target;
    int base_speed;

    auto updateLabelPosition() -> void;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
        target.draw(label, states);
    }
};
