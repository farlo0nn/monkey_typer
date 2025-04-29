#pragma once

#include <SFML/Graphics.hpp>
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
    // void handle(const sf::Event::MouseButtonPressed&);
    auto handle(const sf::Event::TextEntered& textEntered) -> void;
    // void handle(const sf::Event::TouchBegan& touchBegan);

    template <typename T>
    auto handle(const T&) -> void;

    auto config_round() -> void;
    auto drawLog() -> void;

    // Member variables
    sf::RenderWindow m_window;
    sf::Font m_font;
    unsigned int m_fontsize;
    sf::Texture m_enemy_texture;
    sf::Texture m_background_texture;
    sf::Sprite m_background;
    sf::Text m_logText;
    sf::Text m_instructions;
    std::string m_log;
    GeneralGlossary m_general_glossary;
    Spawner m_spawner;
    int m_round_number;
    Typer m_typer;
};
