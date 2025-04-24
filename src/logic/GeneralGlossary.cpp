#include "GeneralGlossary.h"
#include <ios>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <random>


GeneralGlossary::GeneralGlossary()  : __words() {};
GeneralGlossary::GeneralGlossary(std::vector<Word> words) : __words(words) {}


auto GeneralGlossary::get_words() -> std::vector<Word> {
    return __words;
}

auto GeneralGlossary::load(const std::string& path) -> void {

    std::cout << "Loading " << path << "..." << std::endl;
    if (path_exists(path)) {

        auto file = std::fstream(path);

        auto word = std::string();
        while (file >> word) {
            __words.push_back({word.at(0), word, {0, 0}});
        }

    }
    else {
        // throw std::runtime_error("Could not open file " + path);
        std::cout << "Could not open file " << path << std::endl;
    }
}

auto GeneralGlossary::get_random_words(int n) -> std::vector<Word> {
    auto result = std::vector<Word>();
    std::ranges::sample(
    __words,
    std::back_inserter(result),
        n,
        std::mt19937{std::random_device{}()}
    );
    return result;
}

