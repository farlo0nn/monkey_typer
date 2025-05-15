#pragma once

#include <SFML/Graphics.hpp>

#include "config/Difficulty.h"
#include "states/GameState.h"
#include "../entities/components/errors/ErrorBox.h"
#include "../entities/components/menus/GameOverMenu.h"
#include "../entities/components/menus/MainMenu.h"
#include "../entities/components/menus/PauseMenu.h"
#include "../entities/components/hud/Hud.h"
#include "../entities/components/settings/Settings.h"
#include "../entities/utils/PausableClock.h"
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
    sf::RenderWindow m_window;
    MainMenu m_mainMenu;
    PauseMenu m_pauseMenu;
    GameOverMenu m_gameOverMenu;
    Hud m_hud;
    sf::Font m_font;
    sf::Texture m_enemy_texture;
    sf::Texture m_background_texture;
    sf::Sprite m_background;
    sf::Texture m_castle_texture;
    sf::Texture m_destroyed_castle_texture;
    sf::Sprite m_castle;
    ErrorBox errorBox;
    std::queue<std::string> errorQueue;
    sf::Text m_instructions;
    GeneralGlossary m_general_glossary;
    Spawner m_spawner;
    int m_round_number;
    Typer m_typer;
    GameState m_gamestate;
    sf::Texture m_tree_texture;
    std::vector<AnimatedSprite> m_decorations;
    double score;
    PausableClock m_wpm_clock;
    Settings m_settingsPannel;
    sf::Clock m_clock;
    sf::Clock m_errorClock;
    bool m_showingError = false;
    const float m_errorDisplayTime = 3.f;
    Difficulty difficulty;
};
