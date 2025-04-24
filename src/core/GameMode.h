#include <SFML/Graphics.hpp>
#ifndef GAME_MODE_H
#define GAME_MODE_H

namespace gamemode {
    class GameMode {
        public:
        GameMode();
        virtual ~GameMode() = default;

        virtual void handleEvent(const sf::Event& event);
    };
}

#endif //GAME_MODE_H
