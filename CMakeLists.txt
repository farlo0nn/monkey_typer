cmake_minimum_required(VERSION 3.24)
project(Funzies)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY saves DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)


include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.1.4

)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)

add_executable(Funzies src/main.cpp
        src/core/GameState.h
        src/core/GameMode.h
        src/entities/enemy/Enemy.h
        src/core/Game.cpp
        src/core/Game.h
        src/logic/GeneralGlossary.cpp
        src/logic/GeneralGlossary.h
        src/logic/Word.cpp
        src/logic/Word.h
        src/logic/RoundGlossary.cpp
        src/logic/RoundGlossary.h
        src/entities/enemy/EnemyComparator.cpp
        src/entities/enemy/EnemyComparator.h
        src/entities/enemy/EnemySpawnPositions.h
        src/entities/enemy/EnemyState.h
        src/entities/enemy/EnemyState.cpp
        src/entities/enemy/Enemy.cpp
        src/entities/enemy/Spawner.cpp
        src/entities/enemy/Spawner.h
        src/entities/enemy/EnemySpawnPositions.cpp
        src/Constants.h
        src/logic/Typer.cpp
        src/logic/Typer.h
        src/entities/enemy/HighlightedLabel.cpp
        src/entities/enemy/HighlightedLabel.h
        src/entities/enemy/SpawnPosition.h
        src/entities/enemy/AnimatedSprite.cpp
        src/entities/enemy/AnimatedSprite.h
        src/utils.cpp
        src/entities/enemy/Directions.h
        src/entities/components/Button.cpp
        src/entities/components/Button.h
        src/entities/components/BaseMenu.cpp
        src/entities/components/BaseMenu.h
        src/entities/components/GameOverMenu.cpp
        src/entities/components/GameOverMenu.h
        src/entities/components/MainMenu.cpp
        src/entities/components/MainMenu.h
        src/entities/components/PauseMenu.cpp
        src/entities/components/PauseMenu.h
        src/entities/components/Hud.cpp
        src/entities/components/Hud.h
        src/entities/components/Slider.cpp
        src/entities/components/Slider.h
        src/entities/utils/PausableClock.cpp
        src/entities/utils/PausableClock.h
        src/logic/TypeStat.cpp
        src/logic/TypeStat.h
        src/entities/components/Settings.cpp
        src/entities/components/Settings.h
        src/entities/components/Slider.cpp
        src/entities/components/BaseArrowMenu.cpp
        src/entities/components/BaseArrowMenu.h
        src/entities/components/DifficultyArrowMenu.cpp
        src/entities/components/DifficultyArrowMenu.h
        src/core/Fonts.h
        src/entities/components/FontArrowMenu.cpp
        src/entities/components/FontArrowMenu.h
        src/entities/components/ErrorBox.cpp
        src/entities/components/ErrorBox.h
        src/core/Difficulty.cpp
        src/core/Difficulty.h
)

target_link_libraries(Funzies PRIVATE SFML::Graphics fmt)
