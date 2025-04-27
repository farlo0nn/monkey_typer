#include "RoundGlossary.h"
#include <iostream>
#include <algorithm>


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
    this->_glossary[enemy.get_word().first_letter].emplace(enemy);
    this->_enemy_number += 1;
    this->_enemies.push_back(enemy);
}


auto RoundGlossary::print() -> void {
    for (auto const& [first_letter, queue] : _glossary){
        std::cout << "\"" << first_letter << "\"" << " { ";

        auto copy = queue;
        while (!copy.empty()) {
            std::cout << copy.top().get_word().value << ", ";
            copy.pop();
        }

        std::cout << "}\n";
    }
}

auto RoundGlossary::at(const char &index) -> enemy_queue & {
    return this->_glossary.at(index);
}

auto RoundGlossary::as_vector() -> std::vector<Enemy>& {
    return _enemies;
}

auto RoundGlossary::as_string() -> const std::string {
    auto res = std::string();
    for (auto const& enemy : _enemies) {
        res.append(enemy.get_word().value);
        res.append(" ");
    }
    return res;
}

auto RoundGlossary::as_string(std::string sep) -> const std::string {
    auto res = std::string();
    for (auto const& enemy : _enemies) {
        res.append(enemy.get_word().value);
        res.append(sep);
    }
    return res;
}

auto RoundGlossary::get_enemy_number() -> int {
    return this->_enemy_number;
}

auto RoundGlossary::has(const char &letter) -> bool {
    return _glossary.find(letter) != _glossary.end();
}

auto RoundGlossary::pop(char const& first_letter) -> void {
    _enemy_number--;
    _enemies.erase(
        std::remove(
            _enemies.begin(),
            _enemies.end(),
            _glossary[first_letter].top()
        ),
    _enemies.end()
    );
    return _glossary[first_letter].pop();
}

auto RoundGlossary::empty() -> bool {
    return this->_enemy_number == 0;
}

auto RoundGlossary::get_closest_enemy_by_letter(const char &letter) -> std::optional<Enemy> {
    if (this->has(letter)) {
        auto& enemy_q = at(letter);
        return enemy_q.top();

    }
    return std::nullopt;
}