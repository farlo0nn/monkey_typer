#include "RoundGlossary.h"
#include <iostream>


RoundGlossary::RoundGlossary(const std::vector<Word> &words) {
    add(words);
}
RoundGlossary::RoundGlossary(Word word) {
    add(word);
}
RoundGlossary::RoundGlossary() {}


auto RoundGlossary::add(std::vector<Word> words) -> void {

    for (const auto& word : words) {
        this->add(word);
    }
}
auto RoundGlossary::add(Word word) -> void {
    this->_glossary[word.first_letter].emplace(word);
    this->_words_number += 1;
    this->_words.push_back(word);
}


auto RoundGlossary::print() -> void {
    for (auto const& [first_letter, queue] : _glossary){
        std::cout << "\"" << first_letter << "\"" << " { ";

        auto copy = queue;
        while (!copy.empty()) {
            std::cout << copy.top().value << ", ";
            copy.pop();
        }

        std::cout << "}\n";
    }
}

auto RoundGlossary::at(const int &index) -> words_queue & {
    return this->_glossary.at(index);
}

auto RoundGlossary::as_vector() -> std::vector<Word>& {
    return _words;
}

auto RoundGlossary::as_string() -> const std::string {
    auto res = std::string();
    for (auto const& word : _words) {
        res.append(word.value);
        res.append(" ");
    }
    return res;
}

auto RoundGlossary::as_string(std::string sep) -> const std::string {
    auto res = std::string();
    for (auto const& word : _words) {
        res.append(word.value);
        res.append(sep);
    }
    return res;
}

auto RoundGlossary::get_words_number() -> int {
    return this->_words_number;
}

auto RoundGlossary::has(const char &letter) -> bool {
    return _glossary.find(letter) != _glossary.end();
}

auto RoundGlossary::pop(char const& first_letter) -> void {
    _words_number--;
    return _glossary[first_letter].pop();
}

auto RoundGlossary::empty() -> bool {
    return _words_number == 0;
}

