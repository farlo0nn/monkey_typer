#include <iostream>
#include <vector>
#include "RoundGLossary.h"
#include "Word.h"




int input_word(RoundGlossary& glossary, int& score) {

  char letter;
  while (std::cin >> letter && !glossary.has(letter)) {}

  auto& words_queue = glossary.at(letter);

  const Word& target_word = words_queue.top();

  auto next_char_to_match = target_word.value.begin() + 1;

  while (next_char_to_match != target_word.value.end()) {
    const char user_input = std::cin.get();

    if (user_input == '/') {
      std::cout << "Input cancelled.\n";
      return -1;
    }

    if (user_input == *next_char_to_match) {
      ++next_char_to_match;
    }
  }

  score+=target_word.value.size();
  glossary.pop(target_word.first_letter);
  return 0;
}


int main() {

  std::vector<Word> words_vector{
    Word("rabbit", Point(1000, 0)),
    // Word("rooster", Point(10, 10)),
    // Word("rick owens", Point(20, 20)),
    // Word("cock", Point(30, 30)),
    // Word("rock", Point(40, 40)),
    // Word("kakadu", Point(50, 50)),
  };

  auto glossary = RoundGlossary(words_vector);
  glossary.print();

  std::cout << "--- Typing Game ---\n";
  std::cout << "Start typing words:\n";
  auto score = int();

  while (!glossary.empty()) {
    int exit_code = input_word(glossary, score);

    glossary.print();
  }

  std::cout << "your score is: " << score << '\n';
  return 0;
}
