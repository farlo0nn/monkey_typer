#include "Enemy.h"
#include "../../Constants.cpp"

Enemy::Enemy(EnemyState state, const Word& word, const sf::Texture& texture, const sf::Font& font)
    : sprite(texture), state(state), word(word), lives(1), displayed_word(font)
{
    sprite.setTexture(texture);
    set_position(state.position);
    displayed_word.setString(word.value);
}

auto Enemy::update(int round, float deltaTime) -> void {
    auto move_to = std::pair<float, float>{
        state.direction.x * BASE_SPEED * round * 0.4f * deltaTime,
        state.direction.y * BASE_SPEED * round * 0.4f * deltaTime
    };
    sprite.move({move_to.first, move_to.second});
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



auto Enemy::get_lives() const -> int {
    return lives;
}

auto Enemy::damage(int amount) -> void {
    lives -= amount;
}

auto Enemy::is_dead() const -> bool {
    return lives <= 0;
}

auto Enemy::get_enemy_state() const -> EnemyState {
    return state;
}

auto  Enemy::get_displayed_word() const -> const sf::Text& {
    return displayed_word;
}

auto Enemy::set_position(const sf::Vector2f &pos) -> void {
    sprite.setPosition(pos);
}

