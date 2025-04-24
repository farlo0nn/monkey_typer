#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/enemy/Spawner.h"
#include "../logic/GeneralGlossary.h"
#include "../logic/RoundGlossary.h"

class Game
{
public:
    Game();
    auto run() -> void;

private:
    enum class HandlerType
    {
        Classic,
        Visitor,
        Overload,
        Generic,
        Forward
    };

    // Event handlers
    auto  handle(const sf::Event::Closed&) -> void;
    auto handle(const sf::Event::KeyPressed& keyPress) -> void;
    auto handle(const sf::Event::MouseMoved& mouseMoved) -> void;
    // void handle(const sf::Event::MouseButtonPressed&);
    auto handle(const sf::Event::TextEntered& textEntered) -> void;
    // void handle(const sf::Event::TouchBegan& touchBegan);

    template <typename T>
    auto handle(const T&) -> void;

    auto drawLog() -> void;

    // Member variables
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_logText;
    sf::Text m_instructions;
    std::string m_log;
    HandlerType m_handlerType;
    GeneralGlossary m_general_glossary;
    RoundGlossary m_round_glossary;
    Spawner m_spawner;
    int m_round_number;
};
