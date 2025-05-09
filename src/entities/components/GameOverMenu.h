#pragma once
#include "BaseMenu.h"

class GameOverMenu : public BaseMenu {
public:
    GameOverMenu(Callback onRestart, Callback onQuit);
};
