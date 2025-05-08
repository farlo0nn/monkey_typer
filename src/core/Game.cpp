#include "Game.h"

#include <fstream>
#include <iostream>
#include <random>

#include "../Constants.h"
#include "../entities/enemy/EnemySpawnPositions.h"

#include "../utils.cpp"

Game::Game()
    : m_window{sf::VideoMode(WINDOW_SIZE), "MonkeyTyper", sf::Style::Titlebar | sf::Style::Close},
      m_mainMenu(
      [&](){ this->m_gamestate = GameState::GAME; score=0;},
      []() { std::cout << "MENU" << std::endl; },
      [&]() { this->m_window.close(); }
      ),
      m_pauseMenu(
      [&](){ this->m_gamestate = GameState::GAME;},
      [&]() { this->m_gamestate = GameState::MENU; },
      [&]() { this->config_round(); this->m_gamestate = GameState::GAME; score=0;}
      ),
      m_gameOverMenu(
        [&](){ this->m_gamestate = GameState::GAME;},
        [&]() { this->config_round(); this->m_gamestate = GameState::GAME; score=0;}
      ),
      m_hud({WINDOW_SIZE.x/2, WINDOW_SIZE.y - 20}),
      m_font{FONT_PATH},
      m_logText{m_font, "", 20},
      m_instructions{m_font, "Press Enter to change handler type", 24},
      m_spawner(5, 3),
      m_round_number(1),
      m_fontsize(WORD_FONTSIZE),
      m_background_texture("assets/background/background_new.png"),
      m_background(m_background_texture),
      m_castle_texture("assets/sprites/castle/castle0.png"),
      m_destroyed_castle_texture("assets/sprites/castle/castleDestroyed.png"),
      m_gamestate(GameState::MENU),
      m_castle(m_castle_texture),
      active_settings_button_texture("assets/ui/settings/settings_wheel.png"),
      inactive_settings_button_texture("assets/ui/settings/settings_wheel_pressed.png"),
      m_settings_button(active_settings_button_texture, inactive_settings_button_texture),
      m_tree_texture("assets/sprites/decorations/trees.png"),
      score(0)

{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_logText.setFillColor(sf::Color::White);
    m_instructions.setFillColor(sf::Color::White);
    m_instructions.setStyle(sf::Text::Bold);
    m_general_glossary.load(WORDS_PATH);
    m_settings_button.setPosition({WINDOW_SIZE.x - m_settings_button.getGlobalBounds().size.x - 20, 20});
    m_hud.setHighestScore(loadHighestScore());
    config_castle(m_castle_texture);
    config_background();

    config_main_menu();
    config_round();
    config_decorations();
}


auto Game::draw_enemies(std::optional<float> deltaTime) -> void {
    for (auto& [_, queue] : m_typer.glossary.get_glossary()) {
        for (auto& enemy : queue ) {
            if (!enemy.is_active()) {
                if (deltaTime) {
                    enemy.update(m_round_number, *deltaTime);
                }
                m_window.draw(enemy);
            }
            if (enemy.collides(m_castle)) {
                m_gamestate = GameState::GAME_OVER;
                config_castle(m_destroyed_castle_texture);
            }
        }
    }

    if (m_typer.active_enemy) {
        if (deltaTime) {
            m_typer.active_enemy->update(m_round_number, *deltaTime);
        }
        m_window.draw(*m_typer.active_enemy);
        if (m_typer.active_enemy->collides(m_castle)) {
            m_gamestate = GameState::GAME_OVER;
            config_castle(m_destroyed_castle_texture);
        }
    }

}

auto Game::draw_decorations(std::optional<float> deltaTime) -> void {
    for (auto& decoration : m_decorations) {
        if (deltaTime) {
            decoration.update(*deltaTime);
        }
        m_window.draw(decoration);
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
        m_window.draw(m_castle);
        m_window.draw(m_settings_button);


        switch (m_gamestate) {
            case GameState::MENU: {

                clock.restart();


                draw_decorations(std::nullopt);
                draw_enemies(std::nullopt);

                m_window.draw(m_mainMenu);

            }; break;
            case GameState::GAME: {

                m_typer.glossary.add(m_spawner.update());
                m_hud.setScore(score);

                if (score > m_hud.getHighestScore()) {
                    m_hud.setHighestScore(score);
                }

                auto deltaTime = clock.restart().asSeconds();

                draw_decorations(deltaTime);

                draw_enemies(deltaTime);
                m_window.draw(m_hud);

                if (m_typer.glossary.empty() && m_spawner.empty()) {
                    m_gamestate = GameState::BETWEEN_ROUNDS;
                }




            }; break;
            case GameState::PAUSE: {


                clock.restart();

                draw_decorations(std::nullopt);
                draw_enemies(std::nullopt);

                m_window.draw(m_pauseMenu);

            }; break;
            case GameState::BETWEEN_ROUNDS: {
                m_window.draw(m_instructions);
                m_round_number++;
                m_gamestate = GameState::GAME;
                config_round();
                config_castle(m_castle_texture);
            }
            case GameState::GAME_OVER: {
                auto deltaTime = clock.restart().asSeconds();

                draw_decorations(deltaTime);
                m_window.draw(m_castle);
                // m_gamestate = GameState::MENU;
            }; break;
        }

        m_window.draw(m_hud);

        m_window.display();


    }
}



// USER INPUT HANDLERS

auto Game::handle(const sf::Event::Closed&) -> void {
    m_window.close();
}

auto Game::handle(const sf::Event::MouseButtonPressed& mousePressed) -> void {
    std::cout << m_settings_button.getGlobalBounds().contains(sf::Vector2<float>(mousePressed.position)) << std::endl;
    if (m_settings_button.getGlobalBounds().contains(sf::Vector2<float>(mousePressed.position))) {
        m_settings_button.click();
    }


    AbstractMenu* currentMenu = nullptr;

    switch (m_gamestate) {
        case GameState::MENU: currentMenu = &m_mainMenu; break;
        case GameState::PAUSE: currentMenu = &m_pauseMenu; break;
        case GameState::GAME_OVER: currentMenu = &m_gameOverMenu; break;
        default: break;
    }

    if (currentMenu) {
        for (auto& button : currentMenu->get_buttons()) {
            if (button.getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                button.click();
            }
        }
    }



}

auto Game::handle(const sf::Event::MouseButtonReleased& mouseReleased) -> void {
    if (m_gamestate == GameState::MENU) {
        for (auto& button : m_mainMenu.get_buttons()) {
            if (button.isClicked()) {
                button.click();
            }
        }
    }
    else if (m_gamestate == GameState::PAUSE) {
        for (auto& button : m_pauseMenu.get_buttons()) {
            if (button.isClicked()) {
                button.click();
            }
        }
    }
}


auto Game::handle(const sf::Event::TextEntered& textEntered) -> void {
    if (m_gamestate == GameState::GAME) {
        uint32_t u = textEntered.unicode;
        auto c = static_cast<char>(u);
        auto is_typed = m_typer.type(c);
        if (is_typed) {
            score += is_typed;
        };
    }
}

auto Game::handle(const sf::Event::KeyPressed& keyPress) -> void{
    if (m_gamestate == GameState::GAME) {
        if (keyPress.code == sf::Keyboard::Key::Escape) {
            m_gamestate = GameState::PAUSE;
        }
    }
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
    m_typer = Typer();
    m_spawner = Spawner(5, 3);
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

auto Game::config_decorations() -> void {
    auto params = std::vector<std::pair<sf::Vector2f, float>>{

    // UPPER LEFT

    {{100, 150}, 0.7f},
    {{150, 230}, 0.4f},
    {{90, 195}, 0.5f},

    {{200, 170}, 0.7f},
    {{190, 215}, 0.5f},
    {{250, 160}, 0.7f},
    {{300, 240}, 0.4f},
    {{260, 205}, 0.5f},
    {{250, 250}, 0.4f},

    // UPPER RIGHT

    {{960, 70}, 0.7f},
    {{925, 75}, 0.6f},
    {{740, 30}, 0.7f},
    {{735, 30}, 0.45f},


    {{100, 150}, 0.7f},
    {{150, 230}, 0.4f},
    {{90, 195}, 0.5f},

    // MIDDLE RIGHT

    {{700, 370}, 0.7f},
    {{590, 415}, 0.5f},
    {{650, 360}, 0.7f},
    {{700, 440}, 0.4f},
    {{660, 405}, 0.5f},
    {{650, 450}, 0.4f},

    {{860, 405}, 0.5f},
    {{850, 450}, 0.4f},


    // MIDDLE MIDDLE

    {{400, 570}, 0.7f},
    {{290, 615}, 0.5f},
    {{350, 560}, 0.7f},
    {{400, 640}, 0.4f},
    {{360, 605}, 0.5f},
    {{350, 650}, 0.4f},
    {{550, 580}, 0.65f},

    {{860, 405}, 0.5f},
    {{850, 450}, 0.4f},


    // MIDDLE LEFT

    {{390, 0}, 0.7f},
    {{280, 45}, 0.5f},
    {{440, 0}, 0.7f},
    {{490, 40}, 0.4f},
    {{80, 45}, 0.5f},
    {{340, 50}, 0.4f},
    {{540, 30}, 0.65f},

    // LOWER LEFT

    {{70, 400}, 0.65f},
    {{60, 430}, 0.5f},

    };
    for (auto& param : params) {
        auto decoration = AnimatedSprite(m_tree_texture, 6, 0.16f);
        decoration.setPosition(param.first);
        decoration.scale({param.second, param.second});

        m_decorations.push_back(decoration);
    }

}


auto Game::config_main_menu() -> void {
    auto buttons = m_mainMenu.get_buttons();
}


auto Game::loadHighestScore() -> int {
    auto path = "saves/highest_score.txt";
    std::cout << "Loading " << path << "..." << std::endl;
    if (path_exists(path)) {

        auto file = std::fstream(path);
        auto word = std::string();

        file >> word;
        auto score = std::stoi(word);
        std::cout << "Score: " << score << std::endl;
        return score;
    }
    else {
        // throw std::runtime_error("Could not open file " + path);
        std::cout << "Could not open file " << path << std::endl;
    }
    return 0;
}

auto Game::saveHighestScore() -> void {
    auto path = "saves/highest_score.txt";
    std::cout << "Loading " << path << "..." << std::endl;
    if (path_exists(path)) {

        auto file = std::fstream(path);
        auto highestScore = std::to_string(m_hud.getHighestScore());

        file << highestScore;
    }
    else {
        // throw std::runtime_error("Could not open file " + path);
        std::cout << "Could not open file " << path << std::endl;
    }
}

Game::~Game() {
    saveHighestScore();
}