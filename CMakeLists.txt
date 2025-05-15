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

        src/core/states/GameState.h
        src/core/states/GameMode.h

        src/core/Game.cpp
        src/core/Game.h

        src/logic/glossaries/GeneralGlossary.cpp
        src/logic/glossaries/GeneralGlossary.h

        src/logic/word/Word.cpp
        src/logic/word/Word.h

        src/logic/glossaries/RoundGlossary.cpp
        src/logic/glossaries/RoundGlossary.h

        src/entities/enemy/comparators/EnemyComparator.cpp
        src/entities/enemy/comparators/EnemyComparator.h

        src/entities/enemy/spawn/EnemyState.h
        src/entities/enemy/spawn/EnemyState.cpp

        src/entities/enemy/Enemy.cpp
        src/entities/enemy/Enemy.h

        src/entities/enemy/spawn/Spawner.cpp
        src/entities/enemy/spawn/Spawner.h

        src/entities/enemy/spawn/EnemySpawnPositions.cpp
        src/entities/enemy/spawn/EnemySpawnPositions.h

        src/Constants.h


        src/entities/enemy/label/HighlightedLabel.cpp
        src/entities/enemy/label/HighlightedLabel.h
        src/entities/enemy/sprite/AnimatedSprite.cpp
        src/entities/enemy/sprite/AnimatedSprite.h

        src/utils.cpp

        src/entities/enemy/spawn/Directions.h

        src/entities/components/buttons/Button.cpp
        src/entities/components/buttons/Button.h

        src/entities/components/menus/BaseMenu.cpp
        src/entities/components/menus/BaseMenu.h
        src/entities/components/menus/GameOverMenu.cpp
        src/entities/components/menus/GameOverMenu.h
        src/entities/components/menus/MainMenu.cpp
        src/entities/components/menus/MainMenu.h
        src/entities/components/menus/PauseMenu.cpp
        src/entities/components/menus/PauseMenu.h

        src/entities/components/hud/Hud.cpp
        src/entities/components/hud/Hud.h

        src/entities/components/settings/Slider.cpp
        src/entities/components/settings/Slider.h
        src/entities/components/settings/Settings.cpp
        src/entities/components/settings/Settings.h

        src/core/timing/PausableClock.cpp
        src/core/timing/PausableClock.h

        src/logic/typer/TypeStat.cpp
        src/logic/typer/TypeStat.h
        src/logic/typer/Typer.cpp
        src/logic/typer/Typer.h

        src/entities/components/arrowMenus/BaseArrowMenu.cpp
        src/entities/components/arrowMenus/BaseArrowMenu.h
        src/entities/components/arrowMenus/DifficultyArrowMenu.cpp
        src/entities/components/arrowMenus/DifficultyArrowMenu.h
        src/entities/components/arrowMenus/FontArrowMenu.cpp
        src/entities/components/arrowMenus/FontArrowMenu.h

        src/core/config/Fonts.h
        src/core/config/Difficulty.cpp
        src/core/config/Difficulty.h

        src/entities/components/errors/ErrorBox.cpp
        src/entities/components/errors/ErrorBox.h

        src/entities/components/utils/utils.h
        src/core/io/FileManager.cpp
        src/core/io/FileManager.h
)

target_link_libraries(Funzies PRIVATE SFML::Graphics fmt)
