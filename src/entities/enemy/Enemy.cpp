#include "Enemy.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Constants.h"


Enemy::Enemy(const EnemyState &state, Enemies enemyType,  const Word& word, const sf::Font& font, unsigned int fontsize, int base_speed)
    :
    texture(std::make_shared<sf::Texture>()),
    state(state),
    word(word),
    label(font, fontsize),
    active_target(false)
{

    set_position(state.position);
    if (!texture->loadFromFile(getPath(enemyType))) {
        throw std::runtime_error("Incorrect path to texture");
    }

    auto frameCount = getFrameCount(enemyType);

    sprite.emplace(*texture, frameCount);
    sprite->setTexture(*texture);
    sprite->setTextureDirection(state.texture_direction);

    set_position(state.position);
    this->base_speed = base_speed;
    label.setString(word.value);
    label.setColors(sf::Color::Green, sf::Color::White);

    typing_index = 0;
}

auto Enemy::update(int round, float deltaTime) -> void {
    auto velocity = base_speed * (0.4f * round);
    auto move_to = sf::Vector2f{
        state.direction.x * velocity * deltaTime,
        state.direction.y * velocity * deltaTime
    };
    if (state.hasReachedPoint()) {
        state.advanceToNextWaypoint();
    }

    sprite->move(move_to);
    sprite->update(deltaTime);
    state.position = sprite->getPosition();
    update_label_position();
}

auto Enemy::update_label_position() -> void {
    auto sprite_bounds = sprite->getGlobalBounds();
    auto displayed_word_bounds = label.getLocalBounds();
    label.setPosition({
        sprite_bounds.position.x + (sprite_bounds.size.x - displayed_word_bounds.size.x)/2 - displayed_word_bounds.position.x,
        sprite_bounds.position.y - sprite_bounds.size.y - 5.f
    });
}

auto Enemy::get_sprite() const -> const AnimatedSprite& {
    return *sprite;
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
    sprite->setPosition(pos);
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

auto Enemy::is_word_typed() const -> bool {
    return (typing_index == word.value.length());
}


auto Enemy::reset_typing() -> void {
    typing_index = 0;
    label.reset();
    set_active(false);
}

auto Enemy::operator==(const Enemy& other) const -> bool {
    return this->word.value == other.word.value;
};

auto Enemy::collides(const sf::Sprite& other) const -> bool {
    if (other.getGlobalBounds().contains(get_sprite().getPosition())) {
        return true;
    }
    return false;
}

auto Enemy::getFrameCount(const Enemies enemyType) -> int {

    auto frameCount = int();

    switch (enemyType) {
        case Enemies::CHICKEN: frameCount = 14; break;
        case Enemies::RADISH: frameCount = 12; break;
        case Enemies::BAT: frameCount = 7; break;
        case Enemies::BEE: frameCount = 6; break;
        case Enemies::PIG: frameCount = 16; break;
        case Enemies::TRUNK: frameCount = 14; break;
        case Enemies::DUCK: frameCount = 10; break;
        case Enemies::RINO: frameCount = 6; break;
        case Enemies::BUNNY: frameCount = 12; break;
        case Enemies::SLIME: frameCount = 10; break;
        case Enemies::SNAIL: frameCount = 10; break;
        case Enemies::BLUEBIRD: frameCount = 9; break;
        case Enemies::MUSHROOM: frameCount = 16; break;
        case Enemies::COUNT: break;
        default: throw std::invalid_argument("Unknown sprite");
    }

    return frameCount;
}

auto Enemy::getPath(Enemies sprite) -> std::string {
    std::string path;
    switch (sprite) {
        case Enemies::CHICKEN: path = "assets/sprites/enemies/chicken.png"; break;
        case Enemies::RADISH: path = "assets/sprites/enemies/radish.png"; break;
        case Enemies::BAT: path = "assets/sprites/enemies/bat.png"; break;
        case Enemies::BEE: path = "assets/sprites/enemies/bee.png"; break;
        case Enemies::PIG: path = "assets/sprites/enemies/pig.png"; break;
        case Enemies::DUCK: path = "assets/sprites/enemies/duck.png"; break;
        case Enemies::RINO: path = "assets/sprites/enemies/rino.png"; break;
        case Enemies::BUNNY: path = "assets/sprites/enemies/bunny.png"; break;
        case Enemies::SLIME: path = "assets/sprites/enemies/slime.png"; break;
        case Enemies::SNAIL: path = "assets/sprites/enemies/snail.png"; break;
        case Enemies::TRUNK: path = "assets/sprites/enemies/trunk.png"; break;
        case Enemies::BLUEBIRD: path = "assets/sprites/enemies/bluebird.png"; break;
        case Enemies::MUSHROOM: path = "assets/sprites/enemies/mushroom.png"; break;
        case Enemies::COUNT: break;
        default: throw std::invalid_argument("Invalid sprite");
    };
    return path;
}

