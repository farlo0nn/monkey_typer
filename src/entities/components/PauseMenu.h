#pragma once
#include "BaseMenu.h"

class PauseMenu : public BaseMenu {
public:
    PauseMenu(Callback onResume, Callback onMainMenu, Callback onRestart);
};