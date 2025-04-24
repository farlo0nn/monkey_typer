#pragma once
#include "EnemyPosition.h"
#include "../../logic/Word.h"
#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite {
public:

    Enemy(EnemyPosition position, const Word& word, const sf::Texture& texture);

    auto update(float deltaTime, int round) -> void;
    auto get_lives() const -> int;
    auto damage(int amount) -> void;
    auto is_dead() const -> bool;

    auto get_enemy_position() const -> EnemyPosition;
    auto get_word() const -> const Word&;

private:
    EnemyPosition m_position;
    Word m_word;
    int m_lives;
};
