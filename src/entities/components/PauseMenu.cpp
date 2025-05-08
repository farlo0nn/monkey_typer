#include "PauseMenu.h"

PauseMenu::PauseMenu(Callback onResume, Callback onMainMenu, Callback onRestart) : AbstractMenu() {

    auto startButton = create_button("RESUME", {1080/2, 720/2 - 170});

    auto helpButton = create_button("MAIN MENU", {1080/2, 720/2 - 20});
    auto exitButton = create_button("RESTART", {1080/2, 720/2 + 130});

    buttons.emplace_back(startButton);
    buttons.back().onRelease(onResume);

    buttons.emplace_back(helpButton);
    buttons.back().onRelease(onMainMenu);

    buttons.emplace_back(exitButton);
    buttons.back().onRelease(onRestart);
}