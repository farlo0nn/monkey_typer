#pragma once

#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AbstractPopUp : public sf::Drawable {
protected:
    std::vector<sf::Drawable*> components;

    template<typename  T>
    static auto configure_component(T &component, sf::Vector2f position, float scale) -> void;

public:

    AbstractPopUp();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};