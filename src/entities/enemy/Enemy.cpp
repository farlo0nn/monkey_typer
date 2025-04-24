#include "Enemy.h"
#include "../../Constants.cpp"

Enemy::Enemy(EnemyPosition position, const Word& word, const sf::Texture& texture)
    : m_position(position), m_word(word), m_lives(1)
{
    setTexture(texture);
    setPosition(position.coordinates);  // Helper function
}

void Enemy::update(float deltaTime, int round) {

    move(m_position.direction * BASE_SPEED * round * 0.4f * deltaTime);
}

int Enemy::get_lives() const {
    return m_lives;
}

void Enemy::damage(int amount) {
    m_lives -= amount;
}

bool Enemy::is_dead() const {
    return m_lives <= 0;
}

EnemyPosition Enemy::get_enemy_position() const {
    return m_position;
}

const Word& Enemy::get_word() const {
    return m_word;
}
