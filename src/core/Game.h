#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "../entities/components/Button.h"
#include "../entities/components/MainMenu.h"
#include "../entities/enemy/Spawner.h"
#include "../logic/GeneralGlossary.h"
#include "../logic/RoundGlossary.h"
#include "../logic/Typer.h"

class Game
{
public:
    Game();
    auto run() -> void;

private:

    // event handlers
    auto  handle(const sf::Event::Closed&) -> void;
    auto handle(const sf::Event::KeyPressed& keyPress) -> void;
    auto handle(const sf::Event::MouseMoved& mouseMoved) -> void;
    void handle(const sf::Event::MouseButtonPressed&);
    auto handle(const sf::Event::TextEntered& textEntered) -> void;
    // void handle(const sf::Event::TouchBegan& touchBegan);
    auto draw_enemies(std::optional<float> deltaTime) -> void;
    auto draw_decorations(std::optional<float> deltaTime) -> void;

    template <typename T>
    auto handle(const T&) -> void;

    auto config_background() -> void;
    auto config_round() -> void;
    auto config_castle(const sf::Texture& texture) -> void;
    auto config_decorations() -> void;
    auto config_main_menu() -> void;

    // Member variables
    sf::RenderWindow m_window;
    MainMenu m_mainMenu;
    sf::Font m_font;
    unsigned int m_fontsize;
    sf::Texture m_enemy_texture;
    sf::Texture m_background_texture;
    sf::Sprite m_background;
    sf::Texture m_castle_texture;
    sf::Texture m_destroyed_castle_texture;
    sf::Sprite m_castle;
    sf::Text m_logText;
    sf::Text m_instructions;
    std::string m_log;
    GeneralGlossary m_general_glossary;
    Spawner m_spawner;
    int m_round_number;
    Typer m_typer;
    GameState m_gamestate;
    sf::Texture active_settings_button_texture;
    sf::Texture inactive_settings_button_texture;
    sf::Texture m_tree_texture;
    std::vector<AnimatedSprite> m_decorations;
    Button m_settings_button;
};
