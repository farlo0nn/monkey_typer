#pragma once

#include "EnemyState.h"
#include "../../logic/Word.h"
#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable {
public:

    // Constructor needs a font and initial position
    Enemy(EnemyState state, const Word &word, const sf::Texture &texture, const sf::Font &font);

    auto update(int round, float deltaTime) -> void;
    auto get_lives() const -> int;
    auto damage(int amount) -> void;
    auto is_dead() const -> bool;

    auto get_enemy_state() const -> EnemyState;
    auto get_sprite() -> sf::Sprite;

    auto set_position(const sf::Vector2f& pos) -> void;
    auto get_displayed_word() const -> const sf::Text&;
    auto get_word_value() const -> const std::string&;
    auto get_typing_index() const -> int;
    auto get_current_expected_char() const -> char;
    // auto type_next_char()
    auto is_active_target() const -> bool;
    auto set_as_active_target() -> void;

private:
    EnemyState state;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text displayed_word;
    Word word;
    int lives;
    size_t typing_index;
    bool active_target;


    auto update_label_position() -> void;
    auto update_text_color() -> void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
        target.draw(displayed_word, states);
    }
};