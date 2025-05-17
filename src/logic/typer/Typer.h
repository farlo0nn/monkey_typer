#pragma once
#include "../glossaries/RoundGlossary.h"
#include "TypeStat.h"

class Typer {
    auto setActiveEnemy(const char& letter) -> void;
    auto typingLogic(const char& letter) -> void;
public:
    RoundGlossary glossary;
    Enemy* active_enemy = nullptr;
    Typer();

    auto type(const char& letter) -> TypeStat;
    auto resetWordTyping() -> void;
};
