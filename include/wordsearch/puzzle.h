//
// Created by Jennifer Li on 4/21/20.
//

#ifndef FINALPROJECT_PUZZLE_H
#define FINALPROJECT_PUZZLE_H

#include <string>
#include <vector>
#include <iostream>

#include "trie/trie.h"

constexpr size_t kPuzzleSize = 15;
std::string const kHeader = "#spf1.0";
constexpr size_t kFileSize = 3;
constexpr size_t kCharacterSize = 1;
constexpr size_t kMaxWords = 30;

namespace wordsearch {
class Puzzle {
 private:
  // Puzzle full of random letters
  char puzzle_ [kPuzzleSize][kPuzzleSize]{};
  // Solution to puzzle
  char solution_ [kPuzzleSize][kPuzzleSize]{};
  // Trie structure representing list of words to be found
  Trie<char> words_trie_;
  // Vector of words - used for cinder terminal display
  std::vector<std::string> words_vector_;

  // ------------ Methods for setting up puzzle ------------
  // Fill 2d grid with letters of the puzzle
  void CreatePuzzleGrid(std::string& puzzle);
  // Creates trie of words to be found in puzzle
  void CreateTrie(std::string& words_list);

 public:
  // Regular constructor used for testing to access non-static methods
  Puzzle();
  // Overloaded constructor
  explicit Puzzle(std::string& puzzle, std::string& words);
  // checks if trie is empty
  bool IsTrieEmpty();
  // Pretty prints out solution
  void PrintSolution();
  // Returns string representation of solution
  std::string GetSolution();
  // Pretty prints out puzzle
  void PrintPuzzle();
  // Returns string representation of puzzle
  std::string GetPuzzle();
  // Returns reference to vector with word bank
  std::vector<std::string>& GetWordsVector();

  // ------------ Methods for solving puzzle ------------
  // Wrapper method for Solve
  bool Solve(Puzzle& a_single_puzzle);
  // Method for solving a puzzle has a vector of chars to keep track of characters
  // found
  bool Solve(Puzzle& a_single_puzzle, int row, int col);
  // method to find next box in grid
  std::tuple<int, int> FindNextCharacter(int row, int col);

  // These methods help solve in the 8 directions: N,S,E,W,NW,NE,SW,SE
  bool CheckNorth(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckSouth(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckWest(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckNorthWest(Puzzle&a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckNorthEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckSouthWest(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  bool CheckSouthEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);

  // Checks if current word is the full word within a trie
  bool IsFullWord(Trie<char>& trie, std::vector<char>& word);
  // Removes word from trie
  void RemoveWord(std::vector<char> word);

  // ------------ Methods to help with testing ------------
  // Fill 2d grid with letters of the puzzle
  static void CreatePuzzleGrid(std::string& puzzle, char grid[kPuzzleSize][kPuzzleSize]);
  // Creates trie of words to be found in puzzle
  static void CreateTrie(std::string& words_list, Trie<char>& words_trie);
  // Creates vectors of word list
  static void CreateWordListVector(std::string& word_list, std::vector<std::string>& words_vec);
  // Removes word from trie
  void RemoveWord(Trie<char>& trie, std::vector<char> word);
};
} // namespace wordsearch
#endif  // FINALPROJECT_PUZZLE_H
