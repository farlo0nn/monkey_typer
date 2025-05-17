#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(const Callback& onRestart, const Callback& onToMenu) : BaseMenu() {

    auto startButton = createButton("RESTART", {1080/2, 720/2 - 100});
    auto toMenuButton = createButton("TO MENU", {1080/2, 720/2 + 100});

    buttons.emplace_back(startButton);
    buttons.back().onRelease(onRestart);

    buttons.emplace_back(toMenuButton);
    buttons.back().onRelease(onToMenu);
}