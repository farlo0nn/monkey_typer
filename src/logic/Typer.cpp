#include "Typer.h"

#include <iostream>

Typer::Typer() : glossary(RoundGlossary()) {}

auto Typer::set_active_enemy(const char& letter) -> void{
    if (!active_enemy) {
        if (Enemy* enemy = glossary.get_closest_enemy_by_letter(letter)) {
            active_enemy = enemy;
            active_enemy->set_active(true);
        }
    }
}

auto Typer::type(const char &letter) -> void {

    set_active_enemy(letter);

    if (active_enemy) {
        if (active_enemy->get_current_expected_char() == letter) {
            active_enemy->type_next_char();
        }
        if (active_enemy->is_word_typed()) {
            glossary.pop(active_enemy->get_word().first_letter);
            active_enemy = nullptr;
        }
    }
}

auto Typer::reset_word_typing() -> void {
    if (active_enemy) {
        active_enemy->reset_typing();
        active_enemy = nullptr;
    }
}