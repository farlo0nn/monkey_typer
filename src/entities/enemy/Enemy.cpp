#include "Enemy.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Constants.cpp"

Enemy::Enemy(EnemyState state, const Word& word, const sf::Texture& texture, const sf::Font& font, unsigned int fontsize)
    : sprite(texture), state(state), word(word), label(font, fontsize), typing_index(0)
{
    sprite.setTexture(texture);
    set_position(state.position);
    label.setString(word.value);
    label.setColors(sf::Color::White, sf::Color::Red);
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
    auto displayed_word_bounds = label.getLocalBounds();
    label.setPosition({
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
        label.setTypingIndex(this->typing_index);
    }
}

auto Enemy::is_word_typed() -> bool {
    return (typing_index == word.value.length());
}


auto Enemy::reset_typing() -> void {
    typing_index = 0;
    set_active(false);
}

auto Enemy::operator==(const Enemy& other) const -> bool {
    return this->word.value == other.word.value;
};
