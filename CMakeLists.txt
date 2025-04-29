cmake_minimum_required(VERSION 3.24)
project(Funzies)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)


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
        src/modes/MenuMode.cpp
        src/modes/MenuMode.h
        src/modes/PlayingMode.cpp
        src/modes/PlayingMode.h
        src/logic/GeneralGlossary.cpp
        src/logic/GeneralGlossary.h
        src/logic/Word.cpp
        src/logic/Word.h
        src/logic/Point.h
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
        src/entities/enemy/HighlighedLabel.cpp
        src/entities/enemy/HighlighedLabel.h
        src/entities/enemy/SpawnPosition.h
        src/entities/enemy/SpawnPosition.cpp
)

target_link_libraries(Funzies PRIVATE SFML::Graphics fmt)
