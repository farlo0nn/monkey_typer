#include "Button.h"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"

Button::Button(const sf::Texture& textureInactive, const sf::Texture &textureActive, const sf::Font& font, const std::string& text, int fontSize): sprite(textureInactive), label(font) {
    this->textureInactive = textureInactive;
    this->textureActive = textureActive;
    this->label->setString(text);
    this->label->setFont(font);
    this->label->setCharacterSize(fontSize);
}

Button::Button(const sf::Texture &textureInactive, const sf::Texture &textureActive): sprite(textureInactive) {
    this->textureInactive = textureInactive;
    this->textureActive = textureActive;
}


auto Button::onClick(Callback cb) -> void {
    this->clickCallback = cb;
}

auto Button::onRelease(Callback cb) -> void {
    this->releaseCallback = cb;
}

auto Button::click() -> void {
    setActive(!active);
    if (active) {
        sprite.setTexture(textureActive);
        if (clickCallback) {
            clickCallback();
        }
    }
    else {
        sprite.setTexture(textureInactive);
        if (releaseCallback) {
            releaseCallback();
        }
    }
    updateLabelPosition();

}

auto Button::setActive(bool active) -> void {
    this->active = active;
}

auto Button::isClicked() const -> bool {
    return active;
};

auto Button::contains(sf::Vector2f point) const -> bool {
    return sprite.getGlobalBounds().contains(point);
}

auto Button::setOrigin(sf::Vector2f origin) -> void {

    sprite.setOrigin(origin);
    if (label) {
        updateLabelPosition();
    }
}

auto Button::setPosition(sf::Vector2f position) -> void {
    sprite.setPosition(position);
    if (label) {
        updateLabelPosition();
    }
}

auto Button::setScale(sf::Vector2f scale) -> void {
    sprite.setScale(scale);
    if (label) {
        updateLabelPosition();
    }
}

auto Button::getGlobalBounds() -> sf::FloatRect {
    return sprite.getGlobalBounds();
}

auto Button::getLocalBounds() -> sf::FloatRect {
    return sprite.getLocalBounds();
}



auto Button::updateLabelPosition() -> void {
    if (!label) return;
    auto sprite_bounds = sprite.getGlobalBounds();
    auto displayed_word_bounds = label->getLocalBounds();
    label->setOrigin({label->getLocalBounds().size.x / 2, label->getLocalBounds().size.y / 2});
    if (!isClicked()) {
        label->setPosition({
            sprite_bounds.position.x + (sprite_bounds.size.x - displayed_word_bounds.size.x)/2 + displayed_word_bounds.size.x / 2,
            sprite_bounds.position.y + sprite_bounds.size.y/2 - displayed_word_bounds.position.y - 5
        });
    } else {

        label->setPosition({
            sprite_bounds.position.x + (sprite_bounds.size.x - displayed_word_bounds.size.x)/2 + displayed_word_bounds.size.x / 2,
            sprite_bounds.position.y + sprite_bounds.size.y/2 - displayed_word_bounds.position.y - 25 / 2
        });
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
    if (label) target.draw(*label, states);
}




