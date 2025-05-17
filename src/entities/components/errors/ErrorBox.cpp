
#include "ErrorBox.h"

ErrorBox::ErrorBox(const sf::Font &font, const std::string &message) :
    font("assets/fonts/pixelify-sans.ttf"),
    message(this->font, message),
    backgroundTexture("assets/ui/error/errorBoxBanner.png"),
    background(backgroundTexture) {

    this->background.scale({5,0.5});
    this->message.setCharacterSize(24);
    this->message.setFillColor(sf::Color::Red);
}

auto ErrorBox::setPosition(sf::Vector2f position) -> void {
    background.setPosition(position);
    message.setPosition({position.x + 180, position.y + 15});
}

auto ErrorBox::setMessage(const std::string &message) -> void {
    this->message.setString(message);
}


void ErrorBox::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(background, states);
    target.draw(message, states);
}



