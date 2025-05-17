#pragma once

#include <SFML/Graphics.hpp>

#include "config/Difficulty.h"
#include "states/GameState.h"
#include "timing/PausableClock.h"
#include "../entities/components/errors/ErrorBox.h"
#include "../entities/components/menus/GameOverMenu.h"
#include "../entities/components/menus/MainMenu.h"
#include "../entities/components/menus/PauseMenu.h"
#include "../entities/components/hud/Hud.h"
#include "../entities/components/settings/Settings.h"
#include "../entities/enemy/spawn/Spawner.h"
#include "../logic/glossaries/GeneralGlossary.h"
#include "../logic/glossaries/RoundGlossary.h"
#include "../logic/typer/Typer.h"

class Game
{
public:
    Game();
    ~Game();
    auto run() -> void;

private:

    auto startGame() -> void;

    // event handlers


    auto handle(const sf::Event::Closed&) -> void;
    auto handle(const sf::Event::KeyPressed& keyPress) -> void;
    auto handle(const sf::Event::MouseButtonPressed& mousePressed) -> void;
    auto handle(const sf::Event::MouseButtonReleased& mouseReleased) -> void;
    auto handle(const sf::Event::TextEntered& textEntered) -> void;
    template <typename T>
    auto handle(const T& event) -> void;

    auto drawEnemies(std::optional<float> deltaTime) -> void;
    auto drawDecorations(std::optional<float> deltaTime) -> void;

    auto configBackground() -> void;
    auto configRound() -> void;
    auto configCastle(const sf::Texture& texture) -> void;
    auto configDecorations() -> void;

    auto displayMenuScene(const sf::Drawable *menu, bool to_draw_enemies) -> void;
    auto displayGameScene() -> void;

    auto loadHighestScore() -> int;
    auto saveHighestScore() -> void;

    void displayError(const std::string& message);

    auto setFont(const std::string &font) -> void;
    auto setDifficulty() -> void;

    // Member variables
    sf::RenderWindow window_;

    GameState gamestate_;
    MainMenu mainMenu_;
    PauseMenu pauseMenu_;
    GameOverMenu gameOverMenu_;

    Settings settingsPanel_;

    Hud hud_;

    sf::Font font_;

    sf::Texture background_texture_;
    sf::Texture castle_texture_;
    sf::Texture destroyed_castle_texture_;

    sf::Sprite background_;
    sf::Sprite castle_;

    ErrorBox errorBox_;
    std::queue<std::string> errorQueue_;

    GeneralGlossary general_glossary_;

    int round_number_;
    Difficulty difficulty_;
    Spawner spawner_;
    Typer typer_;
    double score_;

    sf::Texture tree_texture_;
    std::vector<AnimatedSprite> decorations_;

    sf::Clock gameClock_;
    sf::Clock errorClock_;
    PausableClock wpm_clock_;

    bool showingError_ = false;
    const float errorDisplayTime_ = 3.f;
};
