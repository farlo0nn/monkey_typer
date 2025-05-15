#include "RoundGlossary.h"
#include <iostream>
#include <algorithm>

#include "../../entities/enemy/comparators/EnemyComparator.h"


RoundGlossary::RoundGlossary(std::vector<Enemy> &enemies) {
    add(enemies);
}
RoundGlossary::RoundGlossary(Enemy enemy) {
    add(enemy);
}
RoundGlossary::RoundGlossary() {}


auto RoundGlossary::add(const std::vector<Enemy>& enemies) -> void {
    for (auto& enemy : enemies) {
        this->add(enemy);
    }
}
auto RoundGlossary::add(const Enemy& enemy) -> void {
    this->_glossary[enemy.get_word().first_letter].emplace_back(enemy);
    this->_enemy_number += 1;}

auto RoundGlossary::at(const char &index) -> std::deque<Enemy>& {
    return this->_glossary.at(index);
}

auto RoundGlossary::get_enemy_number() const -> int {
    return this->_enemy_number;
}

auto RoundGlossary::has(const char &letter) -> bool {
    return (_glossary.find(letter) != _glossary.end()) && !_glossary[letter].empty();
}

auto RoundGlossary::pop(char const& first_letter) -> void {
    _enemy_number--;
    return _glossary[first_letter].pop_front();
}

auto RoundGlossary::empty() -> bool {
    return this->_enemy_number == 0;
}

auto RoundGlossary::get_closest_enemy_by_letter(const char &letter) -> Enemy* {
    if (this->has(letter)) {
        auto& enemies = at(letter);
        std::ranges::sort(enemies, EnemyComparator());
        return &enemies.front();
    }

    return nullptr;
}

auto RoundGlossary::get_glossary() -> rg::enemy_glossary & {
    return _glossary;
}
