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
  char puzzle_ [kPuzzleSize][kPuzzleSize]{};
  // Trie structure representing list of words to be found
  Trie<char> words_trie_;

  // Fill 2d grid with letters of the puzzle
  void CreatePuzzleGrid(std::string& puzzle);
  // Creates trie of words to be found in puzzle
  void CreateTrie(std::string& words_list);

 public:
  Puzzle();
  // Overloaded constructor
  explicit Puzzle(std::string& puzzle, std::string& words);
  // Allows the altering of the grid
  void ChangeCharacter(int row, int col, char value);
  // Retrieve character in puzzle grid
  char GetCharacter(int row, int col);
//  // Checks for value in trie
//  bool Check(std::vector<char> values);
//  // Removes value in trie
//  void Remove(std::vector<char> values);
  // checks if trie is empty
  bool IsTrieEmpty();

  // ------------ Methods for solving puzzle ------------
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

  // Undo the removal of a character from the board during back tracking
  void UndoRemoval(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters);
  // Checks if current word is the full word within a trie
  bool IsFullWord(Trie<char>& trie, std::vector<char>& word);

  // ------------ Methods to help with testing ------------
  // Fill 2d grid with letters of the puzzle
  static void CreatePuzzleGrid(std::string& puzzle, char grid[kPuzzleSize][kPuzzleSize]);
  // Creates trie of words to be found in puzzle
  static void CreateTrie(std::string& words_list, Trie<char>& words_trie);
  // Creates vectors of word list
  static void CreateWordListVector(std::string& word_list, std::vector<std::string>& words_vec);
};
} // namespace wordsearch
#endif  // FINALPROJECT_PUZZLE_H
