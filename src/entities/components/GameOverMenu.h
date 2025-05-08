#pragma once
#include "AbstractMenu.h"

class GameOverMenu : public AbstractMenu {
public:
    GameOverMenu(Callback onRestart, Callback onQuit);
};
