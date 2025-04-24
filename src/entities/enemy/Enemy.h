#pragma once
#include "EnemyPosition.h"
#include "../../logic/Word.h"


class Enemy {
public:
    EnemyPosition position;
    Word word;
    int lives;
    Enemy(EnemyPosition position, Word word);
};
