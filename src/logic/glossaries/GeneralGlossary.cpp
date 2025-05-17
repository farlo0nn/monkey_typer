#include "GeneralGlossary.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <random>

#include "../../core/io/FileManager.h"


GeneralGlossary::GeneralGlossary() {};
GeneralGlossary::GeneralGlossary(const std::vector<Word> &words) : words(words) {}


auto GeneralGlossary::getWords() -> std::vector<Word> {
    return words;
}

auto GeneralGlossary::load(const std::string& path) -> void {

    std::cout << "Loading " << path << "..." << std::endl;
    if (FileManager::pathExists(path)) {
        try {
            auto word = std::string();
            for (auto line : FileManager::readLines(path)) {
                words.push_back({line.at(0), line, {0, 0}});
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Could not open file " << path << std::endl;
    }
}

auto GeneralGlossary::getRandomWords(const int& n, int minLength, int maxLength) -> std::vector<Word> {
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

