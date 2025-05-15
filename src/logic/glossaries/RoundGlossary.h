#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include "../../entities/enemy/Enemy.h"

namespace rg {
    typedef std::unordered_map<char, std::deque<Enemy>> enemy_glossary;
}

class RoundGlossary {
    rg::enemy_glossary _glossary;
    int _enemy_number = int();

public:
    RoundGlossary(std::vector<Enemy> &enemy);
    RoundGlossary(Enemy enemy);
    RoundGlossary();

    auto add(const std::vector<Enemy>& enemies) -> void;
    auto add(const Enemy& enemy) -> void;
    auto get_glossary() -> rg::enemy_glossary&;
    auto get_enemy_number() const -> int;
    auto at(const char &index) -> std::deque<Enemy>&;
    auto has(const char &letter) -> bool;
    auto empty() -> bool;
    auto pop(char const& first_letter) -> void;
    auto get_closest_enemy_by_letter(const char &letter) -> Enemy*;
};
