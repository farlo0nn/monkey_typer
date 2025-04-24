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
    m_log{},
    m_handlerType{HandlerType::Classic},
    m_general_glossary(),
    m_round_glossary(),
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

    if (m_round_number == 1) {
        m_round_glossary.add(m_general_glossary.get_random_words(m_round_number*5 - 4));
    }

    for (auto word : m_round_glossary.as_vector()) {
        // auto position = ENEMY_SPAWN_POSITIONS.at(SpawnPositions::get_random_spawn_position());
        auto position = EnemyState({100,300});

        // std::cout << position.position.x << " " << position.position.y << std::endl;
        // std::cout << position.direction.x << " " << position.direction.y << std::endl;
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
    if (std::isalpha(c)) {
        m_log.push_back(static_cast<char>(u));
    }
}

auto Game::handle(const sf::Event::KeyPressed& keyPress) -> void{
    if (keyPress.code == sf::Keyboard::Key::Backspace) {
        if (m_log.size() > 0) {
            m_log.pop_back();
        }
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

auto Game::drawLog() -> void {
    if (m_log.size() != 0)
    {
        m_logText.setPosition({50.f, static_cast<float>(1 * 20) + 50.f});
        m_logText.setString(m_log);
        m_window.draw(m_logText);
    }
}

// auto create_enemies() -> std::queue<Enemy> {}

auto Game::run() -> void
{


    // auto m_enemies = sf::Vec

    // for (auto& word : m_round_glossary.as_vector()) {
    //
    //     std::random_device rdev;
    //     std::mt19937 rgen(rdev());
    //     std::uniform_int_distribution<int> idist(0,ENEMY_SPAWN_POSITIONS.size()-1);
    //     auto i = ENEMY_SPAWN_POSITIONS.begin();
    //     std::advance(i, idist(rgen));
    //     auto p = *i;
    //     // fmt::println("{}", p.first);
    //     std::cout << p.second.coordinates.x << " " << p.second.coordinates.y << std::endl;
    //     // word.position = p.second.;
    //     std::cout << word.position.x << " " << word.position.y << std::endl;
    // }

    // auto words_textboxes = std::vector<sf::Text>();

    auto clock = sf::Clock();

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent()) {
            event->visit([this](auto& e) { this->handle(e); });
        }

        m_spawner.update();

        m_window.clear();


        // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        //     sf::Sprite sprite;
        //     sprite.setTexture(texture);
        //     sprite.setPosition(rand() % 800, rand() % 600);
        //     sprites.push_back(sprite);
        // }

        // for (auto word : m_round_glossary.as_vector()) {
        //     auto text = sf::Text(m_font, "", 20);
        //     text.setString(word.value);
        //     text.setCharacterSize(24);
        //     text.setFillColor(sf::Color::White);
        //     // std::cout << word.position.x << " " << word.position.y << std::endl;
        //     text.setPosition(word.position);
        //     words_textboxes.push_back(text);
        // }


        auto deltaTime = clock.restart().asSeconds();

        for (auto enemy : m_spawner.get_active_enemies()) {
            enemy.update(m_round_number, deltaTime);
            m_window.draw(enemy);
        }

        m_window.display();


    }
}