#include "Typer.h"

#include <iostream>



Typer::Typer() : glossary(RoundGlossary()) {}

auto Typer::setActiveEnemy(const char& letter) -> void{
    if (!active_enemy) {
        if (Enemy* enemy = glossary.getClosestEnemyByLetter(letter)) {
            active_enemy = enemy;
            active_enemy->setActive(true);
        }
    }
}

auto Typer::type(const char &letter) -> TypeStat {
    setActiveEnemy(letter);
    auto typeStat = TypeStat();

    if (active_enemy) {
        if (active_enemy->getCurrentExpectedChar() == letter) {
            typeStat.is_correct = true;
            typeStat.word_size = active_enemy->getWord().value.size();
            active_enemy->typeNextChar();

            if (active_enemy->isWordTyped()) {
                glossary.pop(active_enemy->getWord().first_letter);
                typeStat.word_size = active_enemy->getWord().value.size();
                typeStat.is_word_typed = true;
                active_enemy = nullptr;
            }

        } else {
            resetWordTyping();
            typeStat = type(letter);
        }
    }
    return typeStat;
}

auto Typer::resetWordTyping() -> void {
    if (active_enemy) {
        active_enemy->resetTyping();
        active_enemy = nullptr;
    }
}