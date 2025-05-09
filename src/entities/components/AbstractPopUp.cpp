#include "AbstractPopUp.h"

#include "../../Constants.h"


template <typename T>
auto AbstractPopUp::configure_component(T& component, sf::Vector2f position, float scale) -> void {
    component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
    component.setPosition(position);
    component.setScale({scale, scale});
}

AbstractPopUp::AbstractPopUp() {}


void AbstractPopUp::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto& component : components) {
        target.draw(*component, states);
    }
}