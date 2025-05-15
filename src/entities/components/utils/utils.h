#pragma once
#include <SFML/System/Vector2.hpp>

namespace utils {
    template <typename T>
    auto configureComponent(T& component, sf::Vector2f position, float scalex, float scaley) -> void {
        component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
        component.setPosition(position);
        component.setScale({scalex, scaley});
    }

    template <typename T>
    auto configureComponent(T& component, sf::Vector2f position, float scale) -> void {
        utils::configureComponent(component, position, scale, scale);
    }
}
