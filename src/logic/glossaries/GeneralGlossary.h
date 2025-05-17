#pragma once
#include <vector>
#include <filesystem>
#include "../word/Word.h"

class GeneralGlossary {
    std::vector<Word>words;
public:
    GeneralGlossary();
    GeneralGlossary(const std::vector<Word> &words);
    auto getWords() -> std::vector<Word>;
    auto load(const std::string& path) -> void;
    auto getRandomWords(const int &n, int minLength, int maxLength) -> std::vector<Word>;
};