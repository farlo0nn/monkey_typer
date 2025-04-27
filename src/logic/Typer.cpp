#include "Typer.h"

#include <iostream>

Typer::Typer() : glossary(RoundGlossary()) {}

auto Typer::set_active_enemy(const char& letter) -> void {
    if (!active_enemy.has_value()) {
        auto enemy = this->glossary.get_closest_enemy_by_letter(letter);
        if (enemy.has_value()) {
            this->active_enemy = enemy;
            active_enemy->set_active(true);
        }
    }
}

auto Typer::type(const char &letter) -> void {

    this->set_active_enemy(letter);

    if (active_enemy.has_value()) {
        auto& ae_value = active_enemy.value();
        if (ae_value.get_current_expected_char() == letter) {
            ae_value.type_next_char();
        }
        if (this->active_enemy.value().is_word_typed()) {
            this->glossary.pop(this->active_enemy.value().get_word().first_letter);
            this->active_enemy = std::nullopt;
        }
    }
}

auto Typer::reset_word_typing() -> void {
    if (active_enemy.has_value()) {
        this->active_enemy.reset();
        this->active_enemy = std::nullopt;
    }
}