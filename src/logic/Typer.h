#pragma once
#include "RoundGlossary.h"
#include "TypeStat.h"

class Typer {
    auto set_active_enemy(const char& letter) -> void;
public:
    RoundGlossary glossary;
    Enemy* active_enemy = nullptr;
    Typer();

    auto type(const char& letter) -> TypeStat;
    auto reset_word_typing() -> void;
};
