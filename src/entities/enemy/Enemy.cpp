#include "Enemy.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Constants.cpp"

Enemy::Enemy(EnemyState state, const Word& word, const sf::Texture& texture, const sf::Font& font)
    : sprite(texture), state(state), word(word), displayed_word(font), typing_index(0)
{
    sprite.setTexture(texture);
    set_position(state.position);
    displayed_word.setString(word.value);
    displayed_word.setFillColor(sf::Color::White);
}

auto Enemy::update(int round, float deltaTime) -> void {
    auto velocity = BASE_SPEED * (0.4f * round);
    auto move_to = sf::Vector2f{
        state.direction.x * velocity * deltaTime,
        state.direction.y * velocity * deltaTime
    };
    sprite.move(move_to);
    update_label_position();
}

auto Enemy::update_label_position() -> void {
    auto sprite_bounds = sprite.getGlobalBounds();
    auto displayed_word_bounds = displayed_word.getLocalBounds();
    displayed_word.setPosition({
        sprite_bounds.position.x + (sprite_bounds.size.x - displayed_word_bounds.size.x)/2 - displayed_word_bounds.position.x,
        sprite_bounds.position.y - sprite_bounds.size.y - 5.f
    });
}

auto Enemy::get_sprite() const -> const sf::Sprite& {
    return sprite;
}

auto Enemy::get_word() const -> const Word & {
    return word;
}

auto Enemy::get_enemy_state() const -> EnemyState {
    return state;
}

auto  Enemy::get_displayed_word() const -> const sf::Text& {
    return displayed_word;
}

auto Enemy::get_typing_index() const -> int {
    return typing_index;
}

auto Enemy::set_position(const sf::Vector2f &pos) -> void {
    sprite.setPosition(pos);
}

auto Enemy::is_active() const -> bool {
    return this->active_target;
}

auto Enemy::set_active(bool active) -> void {
    this->active_target = active;
    this->update_text_color();
}

auto Enemy::get_current_expected_char() const -> char {
    if (typing_index < word.value.length()) {
        return word.value[this->typing_index];
    }
    return '\0';
}

auto Enemy::type_next_char() -> void {
    if (this->typing_index < word.value.length()) {
        this->typing_index++;
    }
    update_text_color();
}

auto Enemy::is_word_typed() -> bool {
    return (typing_index == word.value.length());
}


auto Enemy::reset_typing() -> void {
    typing_index = 0;
    update_text_color();
    set_active(false);
}

auto Enemy::update_text_color() -> void {
    // displayed_word.setFillColor(sf::Color::White);

    if (active_target) {
        displayed_word.setFillColor(sf::Color::Green);
    }
}

auto Enemy::operator==(const Enemy& other) const -> bool {
    return this->word.value == other.word.value;
};