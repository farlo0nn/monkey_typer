#pragma once
#include "BaseMenu.h"

class MainMenu : public BaseMenu {
public:
    MainMenu(Callback onStart, Callback onHelp, Callback onExit);
};