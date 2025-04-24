#pragma once
#include <iostream>

#include "EnemyState.h" // Assuming this exists
#include "../../logic/Word.h" // Assuming this exists and has a get_string() method
#include <SFML/Graphics.hpp>

// Assume EnemyState enum is defined somewhere (e.g., in EnemyState.h)

class Enemy : public sf::Drawable {
public:

    // Constructor needs a font and initial position
    Enemy(EnemyState state, const Word &word, const sf::Texture &texture, const sf::Font &font);

    auto update(int round, float deltaTime) -> void;
    auto get_lives() const -> int;
    auto damage(int amount) -> void;
    auto is_dead() const -> bool;

    auto get_enemy_state() const -> EnemyState;

    auto set_position(const sf::Vector2f& pos) -> void;
    auto get_displayed_word() const -> const sf::Text&;

private:
    EnemyState state;
    sf::Sprite sprite;
    sf::Texture texture; // Store texture if sprite doesn't keep a reference (SFML sprite copies the texture data)
    sf::Text displayed_word; // This is your label text object
    Word word; // Store the word object
    int lives;

    auto update_label_position() -> void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
        target.draw(displayed_word, states);
    }
};