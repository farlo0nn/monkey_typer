#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(Callback onRestart, Callback onQuit) : BaseMenu() {

    auto startButton = create_button("RESTART", {1080/2, 720/2 - 100});
    auto quitButton = create_button("QUIT", {1080/2, 720/2 + 100});

    buttons.emplace_back(startButton);
    buttons.back().onRelease(onRestart);

    buttons.emplace_back(quitButton);
    buttons.back().onRelease(onQuit);
}