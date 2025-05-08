#pragma once
#include "AbstractMenu.h"

class PauseMenu : public AbstractMenu {
public:
    PauseMenu(Callback onResume, Callback onMainMenu, Callback onRestart);
};