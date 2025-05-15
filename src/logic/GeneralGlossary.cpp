#include "GeneralGlossary.h"
#include <ios>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <random>


GeneralGlossary::GeneralGlossary() {};
GeneralGlossary::GeneralGlossary(const std::vector<Word> &words) : words(words) {}


auto GeneralGlossary::get_words() -> std::vector<Word> {
    return words;
}

auto GeneralGlossary::load(const std::string& path) -> void {

    std::cout << "Loading " << path << "..." << std::endl;
    if (path_exists(path)) {

        auto file = std::fstream(path);

        auto word = std::string();
        while (file >> word) {
            words.push_back({word.at(0), word, {0, 0}});
        }

    }
    else {
        // throw std::runtime_error("Could not open file " + path);
        std::cout << "Could not open file " << path << std::endl;
    }
}

auto GeneralGlossary::get_random_words(const int& n, int minLength, int maxLength) -> std::vector<Word> {
    auto filtered = std::vector<Word>();

    std::ranges::copy_if(
        words,
        std::back_inserter(filtered),
        [minLength, maxLength](const int& len) {
            return len >= minLength && len <= maxLength;
        },
        [](const Word& word) {
            return word.value.size();
        }
    );

    if (filtered.empty()) {
        return {};
    }

    std::vector<Word> result;
    auto numberGenerator = std::mt19937(std::random_device{}());



    if (filtered.size() >= n) {
        // takes sample without duplicates
        std::ranges::sample(filtered, std::back_inserter(result), n, numberGenerator);
    } else {

        // takes sample with duplicates
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.push_back(filtered[numberGenerator() % filtered.size()]);
        }
    }

    return result;
}

