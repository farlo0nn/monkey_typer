#pragma once
#include "AbstractMenu.h"

class MainMenu : public AbstractMenu {
public:
    MainMenu(Callback onStart, Callback onHelp, Callback onExit);
};