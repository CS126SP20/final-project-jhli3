//
// Created by Jennifer Li on 4/21/20.
//

#ifndef FINALPROJECT_PUZZLE_H
#define FINALPROJECT_PUZZLE_H

#include <string>
#include <vector>

#include "solver.h"
#include "trie/trie.h"

constexpr size_t kPuzzleSize = 15;

namespace wordsearch {
class Puzzle {
 private:
  // Puzzle full of random letters
  char puzzle_ [kPuzzleSize][kPuzzleSize];
  // Trie structure representing list of words to be found
  Trie<char> words_trie_;

  // Fill 2d grid with letters of the puzzle
  void CreatePuzzleGrid(std::string& puzzle);
  // Creates trie of words to be found in puzzle
  void CreateTrie(std::string& words_list);

 public:
  // Overloaded constructor
  explicit Puzzle(std::string& puzzle, std::string& words);
  // Solve the puzzle
  void Solve();

  // Methods to help with testing
  // Fill 2d grid with letters of the puzzle
  static void CreatePuzzleGrid(std::string& puzzle, char grid[kPuzzleSize][kPuzzleSize]);
  // Creates trie of words to be found in puzzle
  static void CreateTrie(std::string& words_list, Trie<char> words_trie);
  // Creates vectors of word list
  static void CreateWordListVector(std::string& word_list, std::vector<std::string> words_vec);
};
} // namespace wordsearch
#endif  // FINALPROJECT_PUZZLE_H
