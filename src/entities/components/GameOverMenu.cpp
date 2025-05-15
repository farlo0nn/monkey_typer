#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(const Callback& onRestart, const Callback& onToMenu) : BaseMenu() {

    auto startButton = create_button("RESTART", {1080/2, 720/2 - 100});
    auto toMenuButton = create_button("TO MENU", {1080/2, 720/2 + 100});

    buttons.emplace_back(startButton);
    buttons.back().onRelease(onRestart);

    buttons.emplace_back(toMenuButton);
    buttons.back().onRelease(onToMenu);
}