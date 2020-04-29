//
// Created by Jennifer Li on 4/21/20.
//

#ifndef FINALPROJECT_SOLVER_H
#define FINALPROJECT_SOLVER_H

#include "wordsearch/puzzle.h"

#include <tuple>


namespace wordsearch {
class Solver {
 public:
  // Method for solving a puzzle has a vector of chars to keep track of characters
  // found
  bool Solve(Puzzle a_single_puzzle, std::vector<char> characters);
  // method to find next box in grid
  std::tuple<int, int> FindNextCharacter(int row, int col);

 private:
  // These methods help solve in the 8 directions: N,S,E,W,NW,NE,SW,SE
  bool CheckNorth(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckSouth(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckEast(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckWest(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckNorthWest(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckNorthEast(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckSouthWest(Puzzle a_single_puzzle, std::vector<char> characters);
  bool CheckSouthEast(Puzzle a_single_puzzle, std::vector<char> characters);

};
} // namespace wordsearch

#endif  // FINALPROJECT_SOLVER_H
