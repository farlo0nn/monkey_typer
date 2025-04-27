#pragma once
#include "RoundGlossary.h"

class Typer {
    auto set_active_enemy(const char& letter) -> void;
public:
    RoundGlossary glossary;
    std::optional<Enemy> active_enemy;
    Typer();

    auto type(const char& letter) -> void;
    auto reset_word_typing() -> void;
};
