#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include "Word.h"
#include "WordPriority.h"
typedef std::priority_queue<Word, std::vector<Word>, WordPriority> words_queue;


class RoundGlossary {
    std::unordered_map<char, words_queue> _glossary;
    std::vector<Word> _words;
    int _words_number = int();

    public:
    RoundGlossary(const std::vector<Word> &words);
    RoundGlossary(Word word);
    RoundGlossary();

    auto add(std::vector<Word> words) -> void;
    auto add(Word word) -> void;
    auto print() -> void;
    auto as_vector() -> std::vector<Word>&;
    auto as_string() -> const std::string;
    auto as_string(std::string sep) -> const std::string;
    auto at(const int &index) ->  words_queue&;
    auto get_words_number() -> int;
    auto has(const char &letter) -> bool;
    auto empty() -> bool;
    auto pop(char const& first_letter) -> void;
};
