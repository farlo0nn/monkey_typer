#include "Game.h"
#include "../logic/RoundGlossary.h"
#include "../logic/GeneralGlossary.h"
#include <iostream>
#include <random>

#include "../entities/enemy/EnemyState.h"
#include "../entities/enemy/SpawnPosition.h"
#include "fmt/format.h"

Game::Game()
:   m_window{sf::VideoMode(WINDOW_SIZE), "MonkeyTyper", sf::Style::Titlebar | sf::Style::Close},
    m_font{FONT_PATH},
    m_logText{m_font, "", 20},
    m_instructions{m_font, "Press Enter to change handler type", 24},
    m_spawner(1.5, 3),
    m_round_number(1),
    m_enemy_texture("assets/textures/img.png", false, sf::IntRect({10, 10}, {32, 32}))
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_logText.setFillColor(sf::Color::White);
    m_instructions.setFillColor(sf::Color::White);
    m_instructions.setStyle(sf::Text::Bold);
    m_general_glossary.load(WORDS_PATH);
    config_round();
}

auto Game::config_round() -> void {
    for (auto word : m_general_glossary.get_random_words(m_round_number*5 + 5)) {
        auto position = ENEMY_SPAWN_POSITIONS.at(SpawnPositions::get_random_spawn_position());
        m_spawner.enqueue(
            Enemy(
                position,
                word,
                m_enemy_texture,
                m_font
            )
        );
    }
}

auto Game::handle(const sf::Event::Closed&) -> void {
    m_window.close();
}

auto Game::handle(const sf::Event::TextEntered& textEntered) -> void {
    uint32_t u = textEntered.unicode;
    auto c = static_cast<char>(u);
    m_typer.type(c);

}

auto Game::handle(const sf::Event::KeyPressed& keyPress) -> void{
    if (keyPress.code == sf::Keyboard::Key::Escape) {
        m_typer.reset_word_typing();
    }
}

auto Game::handle(const sf::Event::MouseMoved& mouseMoved) -> void {
    // do not log event
    // m_log.emplace_back("Mouse Moved: " + vec2ToString(mouseMoved.position));
}

template<typename T>
auto Game::handle(const T&) -> void {
    // m_log.push_back("Unprocessed event type");
}

auto Game::run() -> void
{
    auto clock = sf::Clock();

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent()) {
            event->visit([this](auto& e) { this->handle(e); });
        }

        m_typer.glossary.add(m_spawner.update());

        m_window.clear();

        auto deltaTime = clock.restart().asSeconds();


        for (auto& [_, queue] : m_typer.glossary.get_glossary()) {
            for (auto& enemy : queue ) {
                enemy.update(m_round_number, deltaTime);
                m_window.draw(enemy);
            }
        }

        if (m_typer.glossary.empty() && m_spawner.empty()) {
            m_window.draw(m_instructions);
            m_round_number++;
            config_round();
        }

        m_window.display();


    }
}