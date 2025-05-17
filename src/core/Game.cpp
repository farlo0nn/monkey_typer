#include "Game.h"

#include <fstream>
#include <iostream>
#include <random>

#include "../Constants.h"
#include "../entities/enemy/spawn/EnemySpawnPositions.h"

#include "../utils.cpp"
#include "../entities/components/decorations/Decoration.h"
#include "io/FileManager.h"

Game::Game()
    : window_{sf::VideoMode(WINDOW_SIZE), "MonkeyTyper", sf::Style::Close},
      mainMenu_(
          [&]() { startGame(); },
          [&]() { gamestate_ = GameState::SETTINGS; },
          [&]() { window_.close(); }
      ),
      pauseMenu_(
          [&]() {
              this->gamestate_ = GameState::GAME;
              wpm_clock_.start();
          },
          [&]() { this->gamestate_ = GameState::MENU; },
          [&]() { startGame(); }
      ),
      gameOverMenu_(
          [&]() { startGame(); },
          [&]() { this->gamestate_ = GameState::MENU; }
      ),
      hud_({WINDOW_SIZE.x / 2, WINDOW_SIZE.y - 20}),
      errorBox_(font_, ""),
      spawner_(5, 3),
      round_number_(1),
      background_texture_("assets/background/background_new.png"),
      background_(background_texture_),
      castle_texture_("assets/sprites/castle/castle0.png"),
      destroyed_castle_texture_("assets/sprites/castle/castleDestroyed.png"),
      gamestate_(GameState::MENU),
      castle_(castle_texture_),
      tree_texture_("assets/sprites/decorations/trees.png"),
      score_(0)
    {
    window_.setFramerateLimit(60);
    window_.setVerticalSyncEnabled(true);

    general_glossary_.load("assets/words.txt");

    hud_.setHighestScore(loadHighestScore());

    settingsPanel_.getToMenu().onRelease([&]() {
        if (auto valid = settingsPanel_.valid(); valid.first)
            gamestate_ = GameState::MENU;
        else
            errorQueue_.push(valid.second.value());
    });

    settingsPanel_.loadFromFile("saves/settings.txt");
    setDifficulty();
    setFont(settingsPanel_.getFont());

    configCastle(castle_texture_);
    configBackground();
    configDecorations();
}

auto Game::startGame() -> void {
    configRound();
    score_=0;
    round_number_ = 1;
    hud_.setRound(round_number_);
    wpm_clock_.reset();
    gamestate_ = GameState::GAME;
}

// MAIN RUN FUNCTION

auto Game::run() -> void
{
    wpm_clock_.reset();

    while (window_.isOpen())
    {
        while (auto event = window_.pollEvent()) {
            event->visit([this](auto& e) { this->handle(e); });
            if (gamestate_ == GameState::SETTINGS) {
                if (settingsPanel_.systemSettingsMode()) {
                    settingsPanel_.getBaseSpeedSlider().handleEvent(*event, window_);
                    settingsPanel_.getWaveDelaySlider().handleEvent(*event, window_);
                    settingsPanel_.getPerWaveSlider().handleEvent(*event, window_);
                }
                else {
                    settingsPanel_.getMaxWordLengthSlider().handleEvent(*event, window_);
                    settingsPanel_.getMinWordLengthSlider().handleEvent(*event, window_);
                }
            }
        }

        if (gamestate_ == GameState::SETTINGS) {
            setDifficulty();
            setFont(settingsPanel_.getFont());
        }

        // difficulty.show();


        window_.clear();
        window_.draw(background_);
        window_.draw(castle_);



        switch (gamestate_) {
            case GameState::MENU: {
                displayMenuScene(&mainMenu_, false);
            }; break;
            case GameState::PAUSE: {
                displayMenuScene(&pauseMenu_, true);
            }; break;
            case GameState::GAME_OVER: {
                displayMenuScene(&gameOverMenu_, true);
            }; break;
            case GameState::SETTINGS: {
                settingsPanel_.update();
                displayMenuScene(&settingsPanel_, false);
            }; break;
            case GameState::GAME: {
                displayGameScene();
            }; break;
        }

        window_.draw(hud_);

        if (showingError_) {
            if (errorClock_.getElapsedTime().asSeconds() < errorDisplayTime_) {
                window_.draw(errorBox_);
            } else {
                showingError_ = false;
            }
        } else {
            if (!errorQueue_.empty()) {
                displayError(errorQueue_.front());
                errorQueue_.pop();
            }
        }


        window_.display();
    }
}



// USER INPUT HANDLERS

// default input handler
template<typename T>
auto Game::handle(const T& event) -> void {
    return;
}

auto Game::handle(const sf::Event::Closed&) -> void {
    window_.close();
}



auto Game::handle(const sf::Event::MouseButtonPressed& mousePressed) -> void {
    BaseMenu* currentMenu = nullptr;

    switch (gamestate_) {
        case GameState::MENU: currentMenu = &mainMenu_; break;
        case GameState::PAUSE: currentMenu = &pauseMenu_; break;
        case GameState::GAME_OVER: currentMenu = &gameOverMenu_; break;
        default: break;
    }

    if (currentMenu) {
        for (auto& button : currentMenu->getButtons()) {
            if (button.getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                button.click();
            }
        }
    }

    if (gamestate_ == GameState::SETTINGS) {
        for (auto& menu : settingsPanel_.getArrowMenus()) {
            if (menu->getLeftArrow().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                menu->getLeftArrow().click();
            }
            if (menu->getRightArrow().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                menu->getRightArrow().click();
            }
        }
        if (settingsPanel_.getToMenu().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
            settingsPanel_.getToMenu().click();
        }
        else {
            if (settingsPanel_.systemSettingsMode()) {
                if (settingsPanel_.getEnemiesSettings().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                    settingsPanel_.getEnemiesSettings().click();
                }
            }
            else {
                if (settingsPanel_.getSystemSettings().getGlobalBounds().contains(sf::Vector2f(mousePressed.position))) {
                    settingsPanel_.getSystemSettings().click();
                }
            }
        }
    }
}


auto Game::handle(const sf::Event::MouseButtonReleased& mouseReleased) -> void {

    BaseMenu* currentMenu = nullptr;

    switch (gamestate_) {
        case GameState::MENU: currentMenu = &mainMenu_; break;
        case GameState::PAUSE: currentMenu = &pauseMenu_; break;
        case GameState::GAME_OVER: currentMenu = &gameOverMenu_; break;
        default: break;
    }

    if (currentMenu) {
        for (auto& button : currentMenu->getButtons()) {
            if (button.isClicked()) {
                button.click();
            }
        }
    }

    if (gamestate_ == GameState::SETTINGS) {
        for (const auto& menu : settingsPanel_.getArrowMenus()) {
            if (menu->getLeftArrow().isClicked()) {menu->getLeftArrow().click();}
            if (menu->getRightArrow().isClicked()) {menu->getRightArrow().click();}
        }
        if (settingsPanel_.getToMenu().isClicked()) {settingsPanel_.getToMenu().click();}
    }
}


auto Game::handle(const sf::Event::TextEntered& textEntered) -> void {
    if (gamestate_ == GameState::GAME) {
        auto u = textEntered.unicode;
        auto c = static_cast<char>(u);
        auto typeStat = typer_.type(c);
        if (typeStat.is_word_typed) {
            score_ += (typeStat.word_size) * difficulty_.scoreMultiplier;
        };
    }
}

auto Game::handle(const sf::Event::KeyPressed& keyPress) -> void{
    if (gamestate_ == GameState::GAME) {
        if (keyPress.code == sf::Keyboard::Key::Escape) {
            gamestate_ = GameState::PAUSE;
        }
    }
}

// CONFIGS

auto Game::configCastle(const sf::Texture& texture) -> void {
    castle_.setScale({0.75, 0.75});
    castle_.setPosition({WINDOW_SIZE.x/2, WINDOW_SIZE.y/2 - 10});
    castle_.setTexture(texture);
    auto spriteBounds = castle_.getGlobalBounds();

    auto offsetx = (spriteBounds.size.x) / 2.f;
    auto offsety = (spriteBounds.size.y) / 2.f;

    castle_.move({-offsetx, -offsety});
}

auto Game::configBackground() -> void {
    auto windowSize = window_.getSize();
    auto rect = background_.getLocalBounds();

    auto scalex = static_cast<float>(windowSize.x) / rect.size.x;
    auto scaley = static_cast<float>(windowSize.y) / rect.size.y;
    auto scale = std::max(scalex, scaley);

    background_.setScale({scale, scale});

    auto spriteBounds = background_.getGlobalBounds();

    // centers the backgroudn
    auto offsetx = (spriteBounds.size.x - windowSize.x) / 2.f;
    auto offsety = (spriteBounds.size.y - windowSize.y) / 2.f;

    background_.setPosition({-offsetx, -offsety});
}

auto Game::configDecorations() -> void {
    auto params = Decoration::getDecorationParams();
    for (auto& param : params) {
        auto decoration = AnimatedSprite(tree_texture_, 6, 0.16f);
        decoration.setPosition(param.first);
        decoration.scale({param.second, param.second});

        decorations_.push_back(decoration);
    }
}

auto Game::configRound() -> void {
    configCastle(castle_texture_);
    typer_ = Typer();
    spawner_ = Spawner(difficulty_.spawnDelay, difficulty_.spawnPerWave);
    auto words = general_glossary_.getRandomWords((round_number_ + 1)*settingsPanel_.getPerWaveSlider().getValue(), settingsPanel_.getMinWordLengthSlider().getValue(), settingsPanel_.getMaxWordLengthSlider().getValue());


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

        auto enemyType = utils::getRandomEnumOption<Enemies>();

        spawner_.enqueue(
            Enemy(
                state,
                enemyType,
                word,
                font_,
                25,
                difficulty_.baseSpeed
            )
        );
    }
}


// Drawing components and entities
auto Game::drawEnemies(std::optional<float> deltaTime) -> void {
    for (auto& [_, queue] : typer_.glossary.getGlossary()) {
        for (auto& enemy : queue ) {
            if (!enemy.isActive()) {
                if (deltaTime) {
                    enemy.update(round_number_, *deltaTime);
                }
                window_.draw(enemy);
            }
            if (enemy.collides(castle_)) {
                gamestate_ = GameState::GAME_OVER;
                configCastle(destroyed_castle_texture_);
            }
        }
    }

    if (typer_.active_enemy) {
        if (deltaTime) {
            typer_.active_enemy->update(round_number_, *deltaTime);
        }
        window_.draw(*typer_.active_enemy);
        if (typer_.active_enemy->collides(castle_)) {
            gamestate_ = GameState::GAME_OVER;
            configCastle(destroyed_castle_texture_);
        }
    }

}

auto Game::drawDecorations(std::optional<float> deltaTime) -> void {
    for (auto& decoration : decorations_) {
        if (deltaTime) {
            decoration.update(*deltaTime);
        }
        window_.draw(decoration);
    }
}

auto Game::displayMenuScene(const sf::Drawable* menu, bool to_draw_enemies) -> void {
    gameClock_.restart();

    drawDecorations(std::nullopt);
    if (to_draw_enemies) {
        drawEnemies(std::nullopt);
    }
    window_.draw(*menu);
}

auto Game::displayGameScene() -> void {

    typer_.glossary.add(spawner_.update());
    hud_.setScore(score_);

    if (score_ > hud_.getHighestScore()) {
        hud_.setHighestScore(score_);
    }

    hud_.setWPM(score_ / (difficulty_.scoreMultiplier * (5.f * (wpm_clock_.getElapsedTime().asSeconds() / 60.f))));


    auto deltaTime = gameClock_.restart().asSeconds();

    drawDecorations(deltaTime);

    drawEnemies(deltaTime);
    window_.draw(hud_);

    if (typer_.glossary.empty() && spawner_.empty()) {
        round_number_++;
        hud_.setRound(round_number_);
        configRound();
    }
}

void Game::displayError(const std::string& message) {
    errorBox_.setMessage(message);
    errorBox_.setPosition({165, 0 });
    showingError_ = true;
    errorClock_.restart();
}


// filesystem operations

auto Game::loadHighestScore() -> int {
    const auto path = "saves/highest_score.txt";
    auto highest_score = int();
    if (!FileManager::pathExists(path)) {
        errorQueue_.push("No saved highest score found.");
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
        errorQueue_.push("No file to save highest score found.");
    }
    else {
        try {
            auto highestScoreString = std::to_string(hud_.getHighestScore());
            FileManager::writeLines(path, {highestScoreString});
        } catch (const std::length_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

Game::~Game() {
    saveHighestScore();
    settingsPanel_.saveToFile("saves/settings.txt");
}

auto Game::setFont(const std::string& font) -> void {

    auto path = std::string();

    if (font == "Arial") {
        path = "assets/fonts/arial.ttf";
    } else if (font == "Sans") {
        path = "assets/fonts/pixelify-sans.ttf";
    } else if (font == "Miners") {
        path = "assets/fonts/pixelminers.otf";
    } else if (font == "64") {
        path = "assets/fonts/sixtyfour.ttf";
    }

    if (!font_.openFromFile(path)) {
        errorQueue_.push("Failed to open the font file.");
    }
}

auto Game::setDifficulty() -> void {
    difficulty_.update(
        settingsPanel_.getBaseSpeedSlider().getValue(),
        settingsPanel_.getPerWaveSlider().getValue(),
        settingsPanel_.getWaveDelaySlider().getValue()
    );
}