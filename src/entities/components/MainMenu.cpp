#include "MainMenu.h"

MainMenu::MainMenu(Callback onStart, Callback onHelp, Callback onQuit) : AbstractMenu() {

    auto startButton = create_button("START", {1080/2, 720/2 - 170});

    auto helpButton = create_button("HELP", {1080/2, 720/2 - 20});
    auto quitButton = create_button("QUIT", {1080/2, 720/2 + 130});

    buttons.emplace_back(startButton);
    buttons.back().onRelease(onStart);

    buttons.emplace_back(helpButton);
    buttons.back().onRelease(onHelp);

    buttons.emplace_back(quitButton);
    buttons.back().onRelease(onQuit);
}