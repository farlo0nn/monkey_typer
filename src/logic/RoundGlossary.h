#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include "../entities/enemy/Enemy.h"
#include "../entities/enemy/EnemyPriority.h"

typedef std::priority_queue<Enemy, std::vector<Enemy>, EnemyPriority> enemy_queue;

class RoundGlossary {
    std::unordered_map<char, enemy_queue> _glossary;
    std::vector<Enemy> _enemies;
    int _enemy_number = int();

public:
    RoundGlossary(std::vector<Enemy> &enemy);
    RoundGlossary(Enemy enemy);
    RoundGlossary();

    auto add(const std::vector<Enemy>& enemies) -> void;
    auto add(const Enemy& enemy) -> void;
    auto print() -> void;
    auto as_vector() -> std::vector<Enemy>&;
    auto as_string() -> const std::string;
    auto as_string(std::string sep) -> const std::string;
    auto at(const char &index) ->  enemy_queue&;
    auto get_enemy_number() -> int;
    auto has(const char &letter) -> bool;
    auto empty() -> bool;
    auto pop(char const& first_letter) -> void;
    auto get_closest_enemy_by_letter(const char &letter) -> std::optional<Enemy>;
};
