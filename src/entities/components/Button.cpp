#include "Button.h"

#include "SFML/Graphics/RenderTarget.hpp"

Button::Button(const sf::Texture& textureInactive, const sf::Texture &textureActive) : sprite(textureInactive) {
    this->textureInactive = textureInactive;
    this->textureActive = textureActive;
}

auto Button::getPosition() -> sf::Vector2f {
    return sprite.getPosition();
}

auto Button::setPosition(const sf::Vector2f &position) -> void {
    sprite.setPosition(position);
}

auto Button::getGlobalBounds() -> sf::FloatRect {
    return sprite.getGlobalBounds();
}




auto Button::onClick(Callback cb) -> void {
    this->callback = std::move(cb);
}

auto Button::click() -> void {
    setActive(!active);
    if (active) {
        sprite.setTexture(textureActive);
        if (callback) {
            callback();
        }
    }
    else {
        sprite.setTexture(textureInactive);
    }

}

auto Button::setActive(bool active) -> void {
    this->active = active;
}

auto Button::isClicked() -> bool {
    return active;
};