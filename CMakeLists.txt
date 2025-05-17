cmake_minimum_required(VERSION 3.24)
project(MonkeyType)

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

FetchContent_MakeAvailable(SFML)

add_executable(MonkeyType src/main.cpp

        # -- CORE --

        src/core/states/GameState.h

        src/core/Game.cpp
        src/core/Game.h

        src/core/config/Fonts.h
        src/core/config/Difficulty.cpp
        src/core/config/Difficulty.h

        src/core/timing/PausableClock.cpp
        src/core/timing/PausableClock.h

        src/core/io/FileManager.cpp
        src/core/io/FileManager.h

        # -- ENTITIES --

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

        src/entities/enemy/label/HighlightedLabel.cpp
        src/entities/enemy/label/HighlightedLabel.h
        src/entities/enemy/sprite/AnimatedSprite.cpp
        src/entities/enemy/sprite/AnimatedSprite.h

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

        src/entities/components/arrowMenus/BaseArrowMenu.cpp
        src/entities/components/arrowMenus/BaseArrowMenu.h
        src/entities/components/arrowMenus/DifficultyArrowMenu.cpp
        src/entities/components/arrowMenus/DifficultyArrowMenu.h
        src/entities/components/arrowMenus/FontArrowMenu.cpp
        src/entities/components/arrowMenus/FontArrowMenu.h

        src/entities/components/errors/ErrorBox.cpp
        src/entities/components/errors/ErrorBox.h

        src/entities/components/utils/utils.h

        src/entities/components/decorations/Decoration.cpp
        src/entities/components/decorations/Decoration.h

        # -- LOGIC --

        src/logic/glossaries/GeneralGlossary.cpp
        src/logic/glossaries/GeneralGlossary.h
        src/logic/glossaries/RoundGlossary.cpp
        src/logic/glossaries/RoundGlossary.h

        src/logic/word/Word.cpp
        src/logic/word/Word.h



        src/logic/typer/TypeStat.cpp
        src/logic/typer/TypeStat.h
        src/logic/typer/Typer.cpp
        src/logic/typer/Typer.h

        # -- OTHER --

        src/Constants.h
        src/utils.cpp
)

target_link_libraries(MonkeyType PRIVATE SFML::Graphics)
