#include "Game.h"

#include <fstream>
#include <iostream>
#include <random>

#include "states/GameMode.h"
#include "../Constants.h"
#include "../entities/enemy/spawn/EnemySpawnPositions.h"

#include "../utils.cpp"
#include "io/FileManager.h"

Game::Game()
    : m_window{sf::VideoMode(WINDOW_SIZE), "MonkeyTyper", sf::Style::Close},
      m_mainMenu(
          [&]() { startGame(); },
          [&]() { m_gamestate = GameState::SETTINGS; },
          [&]() { m_window.close(); }
      ),
      m_pauseMenu(
          [&]() {
              this->m_gamestate = GameState::GAME;
              m_wpm_clock.start();
          },
          [&]() { this->m_gamestate = GameState::MENU; },
          [&]() { startGame(); }
      ),
      m_gameOverMenu(
          [&]() { startGame(); },
          [&]() { this->m_gamestate = GameState::MENU; }
      ),
      m_hud({WINDOW_SIZE.x / 2, WINDOW_SIZE.y - 20}),
      errorBox(m_font, ""),
      m_instructions{m_font, "Press Enter to change handler type", 24},
      m_spawner(5, 3),
      m_round_number(1),
      m_background_texture("assets/background/background_new.png"),
      m_background(m_background_texture),
      m_castle_texture("assets/sprites/castle/castle0.png"),
      m_destroyed_castle_texture("assets/sprites/castle/castleDestroyed.png"),
      m_gamestate(GameState::MENU),
      m_castle(m_castle_texture),
      m_tree_texture("assets/sprites/decorations/trees.png"),
      score(0)
    {
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_instructions.setFillColor(sf::Color::White);
    m_instructions.setStyle(sf::Text::Bold);
    m_general_glossary.load("assets/words.txt");
    m_hud.setHighestScore(loadHighestScore());

    m_settingsPannel.getToMenu().onRelease([&]() {
        if (auto valid = m_settingsPannel.valid(); valid.first)
            m_gamestate = GameState::MENU;
        else
            errorQueue.push(valid.second.value());
    });
    m_settingsPannel.loadFromFile("saves/settings.txt");

    setDifficulty();
    setFont(m_settingsPannel.getFont());

    configCastle(m_castle_texture);
    configBackground();
    configDecorations();
}

auto Game::startGame() -> void {
    configRound();
    score=0;
    m_round_number = 1;
    m_hud.setRound(m_round_number);
    m_wpm_clock.reset();
    m_gamestate = GameState::GAME;
}

// MAIN RUN FUNCTION

auto Game::run() -> void
{
    m_wpm_clock.reset();

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent()) {
            event->visit([this](auto& e) { this->handle(e); });
            if (m_gamestate == GameState::SETTINGS) {
                if (m_settingsPannel.systemSettingsMode()) {
                    m_settingsPannel.getBaseSpeedSlider().handleEvent(*event, m_window);
                    m_settingsPannel.getWaveDelaySlider().handleEvent(*event, m_window);
                    m_settingsPannel.getPerWaveSlider().handleEvent(*event, m_window);
                }
                else {
                    m_settingsPannel.getMaxWordLengthSlider().handleEvent(*event, m_window);
                    m_settingsPannel.getMinWordLengthSlider().handleEvent(*event, m_window);
                }
            }
        }

        if (m_gamestate == GameState::SETTINGS) {
            setDifficulty();
            setFont(m_settingsPannel.getFont());
        }

        // difficulty.show();


        m_window.clear();
        m_window.draw(m_background);
        m_window.draw(m_castle);



        switch (m_gamestate) {
            case GameState::MENU: {
                displayMenuScene(&m_mainMenu, false);
            }; break;
            case GameState::PAUSE: {
                displayMenuScene(&m_pauseMenu, true);
            }; break;
            case GameState::GAME_OVER: {
                displayMenuScene(&m_gameOverMenu, true);
            }; break;
            case GameState::SETTINGS: {
                m_settingsPannel.update();
                displayMenuScene(&m_settingsPannel, false);
            }; break;
            case GameState::GAME: {
                displayGameScene();
            }; break;
        }

        m_window.draw(m_hud);

        if (m_showingError) {
            if (m_errorClock.getElapsedTime().asSeconds() < m_errorDisplayTime) {
                m_window.draw(errorBox);
            } else {
                m_showingError = false;
            }
        } else {
            if (!errorQueue.empty()) {
                displayError(errorQueue.front());
                errorQueue.pop();
            }
        }


        m_window.display();


    }
}



// USER INPUT HANDLERS

auto Game::handle(const sf::Event::Closed&) -> void {
    m_window.close();
}

template<typename T>
auto Game::handle(const T& event) -> void {
    return;
}


auto Game::handle(const sf::Event::MouseButtonPressed& mousePressed) -> void {
    BaseMenu* currentMenu = nullptr;

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

    if (m_gamestate == GameState::SETTINGS) {
        for (auto& menu : m_settingsPannel.getArrowMenus()) {
            if (menu->getLeftArrow().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                menu->getLeftArrow().click();
            }
            if (menu->getRightArrow().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                menu->getRightArrow().click();
            }
        }
        if (m_settingsPannel.getToMenu().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
            m_settingsPannel.getToMenu().click();
        }
        else {
            if (m_settingsPannel.systemSettingsMode()) {
                if (m_settingsPannel.getEnemiesSettings().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                    m_settingsPannel.getEnemiesSettings().click();
                }
            }
            else {
                if (m_settingsPannel.getSystemSettings().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                    m_settingsPannel.getSystemSettings().click();
                }
            }
        }
    }
}



auto Game::handle(const sf::Event::MouseButtonReleased& mouseReleased) -> void {

    BaseMenu* currentMenu = nullptr;

    switch (m_gamestate) {
        case GameState::MENU: currentMenu = &m_mainMenu; break;
        case GameState::PAUSE: currentMenu = &m_pauseMenu; break;
        case GameState::GAME_OVER: currentMenu = &m_gameOverMenu; break;
        default: break;
    }

    if (currentMenu) {
        for (auto& button : currentMenu->get_buttons()) {
            if (button.isClicked()) {
                button.click();
            }
        }
    }

    if (m_gamestate == GameState::SETTINGS) {
        for (const auto& menu : m_settingsPannel.getArrowMenus()) {
            if (menu->getLeftArrow().isClicked()) {menu->getLeftArrow().click();}
            if (menu->getRightArrow().isClicked()) {menu->getRightArrow().click();}
        }
        if (m_settingsPannel.getToMenu().isClicked()) {m_settingsPannel.getToMenu().click();}
    }
}


auto Game::handle(const sf::Event::TextEntered& textEntered) -> void {
    if (m_gamestate == GameState::GAME) {
        auto u = textEntered.unicode;
        auto c = static_cast<char>(u);
        auto typeStat = m_typer.type(c);
        if (typeStat.is_word_typed) {
            score += (typeStat.word_size) * difficulty.scoreMultiplier;
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

// CONFIGS

auto Game::configCastle(const sf::Texture& texture) -> void {
    m_castle.setScale({0.75, 0.75});
    m_castle.setPosition({WINDOW_SIZE.x/2, WINDOW_SIZE.y/2 - 10});
    m_castle.setTexture(texture);
    auto spriteBounds = m_castle.getGlobalBounds();

    // Move so that the sprite is centered (and cropped by window automatically)
    auto offsetX = (spriteBounds.size.x) / 2.f;
    auto offsetY = (spriteBounds.size.y) / 2.f;

    m_castle.move({-offsetX, -offsetY});
}

auto Game::configBackground() -> void {
    auto windowSize = m_window.getSize();
    auto rect = m_background.getLocalBounds();

    auto scaleX = static_cast<float>(windowSize.x) / rect.size.x;
    auto scaleY = static_cast<float>(windowSize.y) / rect.size.y;
    auto scale = std::max(scaleX, scaleY);

    m_background.setScale({scale, scale});

    auto spriteBounds = m_background.getGlobalBounds();

    // centers the backgroudn
    auto offsetX = (spriteBounds.size.x - windowSize.x) / 2.f;
    auto offsetY = (spriteBounds.size.y - windowSize.y) / 2.f;

    m_background.setPosition({-offsetX, -offsetY});
}

auto Game::configDecorations() -> void {
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

auto Game::configRound() -> void {
    configCastle(m_castle_texture);
    m_typer = Typer();
    m_spawner = Spawner(difficulty.spawnDelay, difficulty.spawnPerWave);
    auto words = m_general_glossary.get_random_words((m_round_number + 1)*m_settingsPannel.getPerWaveSlider().getValue(), m_settingsPannel.getMinWordLengthSlider().getValue(), m_settingsPannel.getMaxWordLengthSlider().getValue());


    auto spawn_positions = std::vector<SpawnPosition>();
    for (const auto& [pos, _] : ENEMY_SPAWN_POSITIONS) {
        spawn_positions.push_back(pos);
    }

    std::ranges::shuffle(spawn_positions, std::mt19937{std::random_device{}()});

    auto spawn_index = 0;
    for (auto word : words) {

        // rearrange position if all of them were covered
        if (spawn_index >= spawn_positions.size()) {
            std::ranges::shuffle(spawn_positions, std::mt19937{std::random_device{}()});
            spawn_index = 0;
        }

        auto pos = spawn_positions[spawn_index];
        auto state = ENEMY_SPAWN_POSITIONS.at(pos);
        spawn_index++;

        auto animated_sprite = getAnimatedSprite(utils::get_random_enum_option<as::AnimatedSprites>());
        animated_sprite.setTextureDirection(state.texture_direction);
        std::cout << m_font.getInfo().family << std::endl;
        m_spawner.enqueue(
            Enemy(
                state,
                animated_sprite,
                word,
                m_font,
                25,
                difficulty.baseSpeed
            )
        );
    }
}


// Drawing components and entities
auto Game::drawEnemies(std::optional<float> deltaTime) -> void {
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
                configCastle(m_destroyed_castle_texture);
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
            configCastle(m_destroyed_castle_texture);
        }
    }

}

auto Game::drawDecorations(std::optional<float> deltaTime) -> void {
    for (auto& decoration : m_decorations) {
        if (deltaTime) {
            decoration.update(*deltaTime);
        }
        m_window.draw(decoration);
    }
}

auto Game::displayMenuScene(const sf::Drawable* menu, bool to_draw_enemies) -> void {
    m_clock.restart();

    drawDecorations(std::nullopt);
    if (to_draw_enemies) {
        drawEnemies(std::nullopt);
    }
    m_window.draw(*menu);
}

auto Game::displayGameScene() -> void {

    m_typer.glossary.add(m_spawner.update());
    m_hud.setScore(score);

    if (score > m_hud.getHighestScore()) {
        m_hud.setHighestScore(score);
    }

    m_hud.setWPM(score / (difficulty.scoreMultiplier * (5.f * (m_wpm_clock.getElapsedTime().asSeconds() / 60.f))));


    auto deltaTime = m_clock.restart().asSeconds();

    drawDecorations(deltaTime);

    drawEnemies(deltaTime);
    m_window.draw(m_hud);

    if (m_typer.glossary.empty() && m_spawner.empty()) {
        m_round_number++;
        m_hud.setRound(m_round_number);
        configRound();
    }
}

void Game::displayError(const std::string& message) {
    errorBox.setMessage(message);
    errorBox.setPosition({165, 0 });
    m_showingError = true;
    m_errorClock.restart();
}


// filesystem operations

auto Game::loadHighestScore() -> int {
    const auto path = "saves/highest_score.txt";
    auto highest_score = int();
    if (!FileManager::pathExists(path)) {
        errorQueue.push("No saved highest score found.");
    }
    else {
        try {
            highest_score = std::stoi(FileManager::readLines(path)[0]);
        } catch (const std::length_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return highest_score;
}

auto Game::saveHighestScore() -> void {
    const auto path = "saves/highest_score.txt";

    if (!FileManager::pathExists(path)) {
        errorQueue.push("No file to save highest score found.");
    }
    else {
        try {
            auto highestScoreString = std::to_string(m_hud.getHighestScore());
            FileManager::writeLines(path, {highestScoreString});
        } catch (const std::length_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

Game::~Game() {
    saveHighestScore();
    m_settingsPannel.saveToFile("saves/settings.txt");
}

auto Game::setFont(const std::string& font) -> void {
    if (font == "Arial") {
        m_font.openFromFile("assets/fonts/arial.ttf");
    } else if (font == "Sans") {
        m_font.openFromFile("assets/fonts/pixelify-sans.ttf");
    } else if (font == "Miners") {
        m_font.openFromFile("assets/fonts/pixelminers.otf");
    } else if (font == "64") {
        m_font.openFromFile("assets/fonts/sixtyfour.ttf");
    }
}

auto Game::setDifficulty() -> void {
    difficulty.update(
        m_settingsPannel.getBaseSpeedSlider().getValue(),
        m_settingsPannel.getPerWaveSlider().getValue(),
        m_settingsPannel.getWaveDelaySlider().getValue()
    );
}