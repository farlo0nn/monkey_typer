#include "Hud.h"

#include "../../Constants.h"

Hud::Hud(const sf::Vector2f& position)
    : background_texture("assets/ui/hud/hud_banner.png"),
      background(background_texture),
      font("assets/fonts/pixelify-sans.ttf"),
      fontSize(32),
      wpm(font, "WPM:", 0),
      score(font, "Score:", 0),
      highestScore(font, "Highest:", 0)
{
    configure_component(background, position, 2, 1.3);
    auto backgroundBounds = background.getLocalBounds();
    wpm.setValue(0);
    wpm.setPosition({position.x - backgroundBounds.size.x/2 + 450 ,position.y - backgroundBounds.size.y/2});
    score.setPosition({position.x - backgroundBounds.size.x/2 ,position.y - backgroundBounds.size.y/2});
    highestScore.setPosition({position.x - backgroundBounds.size.x/2 + 200 ,position.y - backgroundBounds.size.y/2});
}

template <typename T>
auto Hud::configure_component(T& component, sf::Vector2f position, float scalex, float scaley) -> void {
    component.setOrigin({component.getLocalBounds().size.x / 2, component.getLocalBounds().size.y / 2});
    component.setPosition(position);
    component.setScale({scalex, scaley});
}

auto Hud::scale(sf::Vector2f scale) -> void {
    this->background.scale(scale);
}

auto Hud::setPosition(sf::Vector2f position) -> void {
    this->background.setPosition(position);
}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(wpm, states);
    target.draw(score, states);
    target.draw(highestScore, states);
}

auto Hud::setScore(int score) -> void {
    this->score.setValue(score);
};
auto Hud::setHighestScore(int highestScore) -> void {
    this->highestScore.setValue(highestScore);
};

auto Hud::setEnemiesKilled(bool enemiesKilled) -> void {

};
auto Hud::setWPM (float wpm) -> void {
    this->wpm.setValue(wpm);
};

auto Hud::getHighestScore() const -> int {
    return highestScore.getValue();
}
