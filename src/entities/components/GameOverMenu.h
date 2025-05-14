#pragma once
#include "BaseMenu.h"

class GameOverMenu : public BaseMenu {
public:
    GameOverMenu(const Callback &onRestart, const Callback &onQuit);
};
