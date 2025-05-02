#include "Game.h"

#include <iostream>
#include <random>

#include "../Constants.h"

#include "../logic/RoundGlossary.h"
#include "../logic/GeneralGlossary.h"

#include "../entities/enemy/EnemySpawnPositions.h"
#include "../entities/enemy/Directions.h"

#include "../utils.cpp"

Game::Game()
    : m_window{sf::VideoMode(WINDOW_SIZE), "MonkeyTyper", sf::Style::Titlebar | sf::Style::Close},
    m_font{FONT_PATH},
    m_logText{m_font, "", 20},
    m_instructions{m_font, "Press Enter to change handler type", 24},
    m_spawner(5, 3),
    m_round_number(1),
    m_fontsize(WORD_FONTSIZE),
    m_enemy_texture("assets/sprites/enemies/chicken.png"),
    m_background_texture("assets/background/background_new.png"),
    m_background(m_background_texture),
    m_castle_texture("assets/sprites/castle/castle0.png"),
    m_destroyed_castle_texture("assets/sprites/castle/castleDestroyed.png"),
    m_gamestate(GameState::GAME),
    m_castle(m_castle_texture)
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_logText.setFillColor(sf::Color::White);
    m_instructions.setFillColor(sf::Color::White);
    m_instructions.setStyle(sf::Text::Bold);
    m_general_glossary.load(WORDS_PATH);


    config_castle(m_castle_texture);
    config_background();
    config_round();
}


auto Game::draw_enemies(float deltaTime) -> void {
    for (auto& [_, queue] : m_typer.glossary.get_glossary()) {
        for (auto& enemy : queue ) {
            if (!enemy.is_active()) {
                enemy.update(m_round_number, deltaTime);
                m_window.draw(enemy);
            }
            if (enemy.collides(m_castle)) {
                m_gamestate = GameState::GAME_OVER;
                config_castle(m_destroyed_castle_texture);
            }
        }
    }

    if (m_typer.active_enemy) {
        m_typer.active_enemy->update(m_round_number, deltaTime);
        m_window.draw(*m_typer.active_enemy);
        if (m_typer.active_enemy->collides(m_castle)) {
            m_gamestate = GameState::GAME_OVER;
            config_castle(m_destroyed_castle_texture);
        }
    }

}

// MAIN RUN FUNCTION

auto Game::run() -> void
{
    auto clock = sf::Clock();

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent()) {
            event->visit([this](auto& e) { this->handle(e); });
        }

        m_window.clear();
        m_window.draw(m_background);

        switch (m_gamestate) {
            case GameState::MENU: {

            }; break;
            case GameState::GAME: {
                m_typer.glossary.add(m_spawner.update());

                auto deltaTime = clock.restart().asSeconds();

                draw_enemies(deltaTime);

                if (m_typer.glossary.empty() && m_spawner.empty()) {
                    m_gamestate = GameState::BETWEEN_ROUNDS;
                }

                m_window.draw(m_castle);
            }; break;
            case GameState::PAUSE: {
            }; break;
            case GameState::BETWEEN_ROUNDS: {
                m_window.draw(m_instructions);
                m_round_number++;
                m_gamestate = GameState::GAME;
                config_round();
                config_castle(m_castle_texture);
            }
            case GameState::GAME_OVER: {
                m_window.draw(m_castle);
            }; break;
        }



        m_window.display();


    }
}



// USER INPUT HANDLERS

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




// CONFIGS

auto Game::config_castle(const sf::Texture& texture) -> void {
    m_castle.setScale({0.75, 0.75});
    m_castle.setPosition({WINDOW_SIZE.x/2, WINDOW_SIZE.y/2 - 10});
    m_castle.setTexture(texture);
    sf::FloatRect spriteBounds = m_castle.getGlobalBounds();

    // Move so that the sprite is centered (and cropped by window automatically)
    float offsetX = (spriteBounds.size.x) / 2.f;
    float offsetY = (spriteBounds.size.y) / 2.f;

    m_castle.move({-offsetX, -offsetY});
}

auto Game::config_background() -> void {
    sf::Vector2u windowSize = m_window.getSize();
    sf::FloatRect rect = m_background.getLocalBounds();

    float scaleX = static_cast<float>(windowSize.x) / rect.size.x;
    float scaleY = static_cast<float>(windowSize.y) / rect.size.y;

    // Choose the larger scale to fully cover the window
    float scale = std::max(scaleX, scaleY);

    m_background.setScale({scale, scale});

    sf::FloatRect spriteBounds = m_background.getGlobalBounds();

    // Move so that the sprite is centered (and cropped by window automatically)
    float offsetX = (spriteBounds.size.x - windowSize.x) / 2.f;
    float offsetY = (spriteBounds.size.y - windowSize.y) / 2.f;

    m_background.setPosition({-offsetX, -offsetY});
}

auto Game::config_round() -> void {
    for (auto word : m_general_glossary.get_random_words(m_round_number*5 + 5)) {
        auto state = ENEMY_SPAWN_POSITIONS.at(utils::get_random_enum_option<SpawnPosition>());
        auto animated_sprite = getAnimatedSprite(utils::get_random_enum_option<as::AnimatedSprites>());
        animated_sprite.setTextureDirection(state.texture_direction);
        m_spawner.enqueue(
            Enemy(
                state,
                animated_sprite,
                word,
                m_font,
                m_fontsize
            )
        );
    }
}
