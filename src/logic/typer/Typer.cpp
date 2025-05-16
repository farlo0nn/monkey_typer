#include "Typer.h"

#include <iostream>



Typer::Typer() : glossary(RoundGlossary()) {}

auto Typer::setActiveEnemy(const char& letter) -> void{
    if (!active_enemy) {
        if (Enemy* enemy = glossary.getClosestEnemyByLetter(letter)) {
            active_enemy = enemy;
            active_enemy->set_active(true);
        }
    }
}

auto Typer::type(const char &letter) -> TypeStat {
    setActiveEnemy(letter);
    auto typeStat = TypeStat();

    if (active_enemy) {
        if (active_enemy->get_current_expected_char() == letter) {
            typeStat.is_correct = true;
            typeStat.word_size = active_enemy->get_word().value.size();
            active_enemy->type_next_char();

            if (active_enemy->is_word_typed()) {
                glossary.pop(active_enemy->get_word().first_letter);
                typeStat.word_size = active_enemy->get_word().value.size();
                typeStat.is_word_typed = true;
                active_enemy = nullptr;
            }

        } else {
            resetWordTyping();
            setActiveEnemy(letter);
            typeStat = type(letter);
        }
    }
    return typeStat;
}

auto Typer::resetWordTyping() -> void {
    if (active_enemy) {
        active_enemy->reset_typing();
        active_enemy = nullptr;
    }
}