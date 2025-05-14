#pragma once
#include "BaseArrowMenu.h"
#include "../../core/Difficulties.h"

class DifficultyArrowMenu : public BaseArrowMenu {
public:
    DifficultyArrowMenu(const sf::Vector2f &position);
    auto getValue() const -> std::string;
    auto setValue(const std::string &value) -> void;
};


inline auto to_string(Difficulty d) -> std::string;
inline auto from_string(const std::string& str) -> Difficulty;