#pragma once
#include <vector>
#include <filesystem>
#include "Word.h"


namespace {
    namespace fs = std::filesystem;

    bool path_exists(const std::string& path) {
        try {
            return fs::exists(fs::path(path));
        } catch (const fs::filesystem_error& e){
            return false;
        }
    }
}

class GeneralGlossary {
    std::vector<Word>__words;
public:
    GeneralGlossary();
    GeneralGlossary(const std::vector<Word> &words);
    auto get_words() -> std::vector<Word>;
    auto load(const std::string& path) -> void;
    auto get_random_words(const int &n) -> std::vector<Word>;
};