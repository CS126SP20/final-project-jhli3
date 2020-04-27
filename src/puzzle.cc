//
// Created by Jennifer Li on 4/21/20.
//

#include <wordsearch/puzzle.h>

namespace wordsearch {
// Overloaded constructor
Puzzle::Puzzle(std::string& puzzle, std::string& words) {
  // load 2d array with values from puzzle string
  CreatePuzzleGrid(puzzle);
  // create trie of words
  CreateTrie(words);
}

// Solve the puzzle
void Puzzle::Solve() {

}

// Fill 2d grid with letters of the puzzle
void Puzzle::CreatePuzzleGrid(std::string& puzzle) {
  // Keeps track of the character in the puzzle
  int char_counter = 0;
  // iterates through 2d array
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int column = 0; column < kPuzzleSize; column++) {
      puzzle_[row][column] = puzzle.at(char_counter);
      char_counter++;
    }
  }
}

// Creates trie of words to be found in puzzle
// each word needs to be split into a vector
void Puzzle::CreateTrie(std::string& words) {
  std::vector<std::string> words_list;
  CreateWordListVector(words, words_list);

  // Create new trie
  Trie<char> temp;

  // add each word into trie
  for (std::string word : words_list) {
    // each word has a vector to it
    // code derived from:
    // https://www.techiedelight.com/convert-string-vector-chars-cpp/
    std::vector<char> word_vec(word.begin(), word.end());
    temp.add(word_vec);
    word_vec.clear();
  }
  words_trie_ = temp;
}

void Puzzle::CreateWordListVector(std::string& words, std::vector<std::string>& words_list) {
  // convert list of words into a char array
  char char_of_words[words.size() + 1];
  strcpy(char_of_words, words.c_str());
  // Returns first token
  char *token = std::strtok(char_of_words, " ");
  // Keep printing tokens while one of the
  // delimiters present in char_of_words[].
  while (token != NULL)
  {
    // adds each word into the
    words_list.push_back(token);
    token = std::strtok(NULL, " ");
  }
}

// --------- Methods to help with testing ---------
void Puzzle::CreatePuzzleGrid(std::string& puzzle, char grid[kPuzzleSize][kPuzzleSize]) {
  // Keeps track of the character in the puzzle
  int char_counter = 0;
  // iterates through 2d array
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int column = 0; column < kPuzzleSize; column++) {
      grid[row][column] = puzzle.at(char_counter);
      char_counter++;
    }
  }
}
// Creates trie of words to be found in puzzle
void Puzzle::CreateTrie(std::string& words, Trie<char>& words_trie) {
  std::vector<std::string> words_list;
  CreateWordListVector(words, words_list);

  // Create new trie
  Trie<char> temp;

  // add each word into trie
  for (std::string word : words_list) {
    // each word has a vector to it
    // code derived from:
    // https://www.techiedelight.com/convert-string-vector-chars-cpp/
    std::vector<char> word_vec(word.begin(), word.end());
    temp.add(word_vec);
    word_vec.clear();
  }
  words_trie = temp;
}

} // namespace wordsearch