#include "MainMenu.h"

MainMenu::MainMenu(Callback onStart, Callback onHelp, Callback onExit) : AbstractMenu() {

    auto startButton = create_button("START", {1080/2, 720/2 - 170});

    auto helpButton = create_button("HELP", {1080/2, 720/2 - 20});
    auto exitButton = create_button("EXIT", {1080/2, 720/2 + 130});

    buttons.emplace_back(startButton);
    buttons.back().onClick(onStart);

    buttons.emplace_back(helpButton);
    buttons.back().onClick(onHelp);

    buttons.emplace_back(exitButton);
    buttons.back().onClick(onExit);
}