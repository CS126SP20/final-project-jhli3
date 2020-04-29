//
// Created by Jennifer Li on 4/21/20.
//

#include "wordsearch/solver.h"

namespace wordsearch {
// Method for solving a puzzle has a vector of chars to keep track of characters
// found
bool Solver::Solve(Puzzle a_single_puzzle, std::vector<char> characters) {
  if (a_single_puzzle.IsTrieEmpty()) { // if all words have been found then success!
    return true;
  }
  return false;
}
// method to find next box in grid
std::tuple<int, int> Solver::FindNextCharacter(int row, int col) {
  // beginning the entire solve algorithm at the first column
  if (row == 0 && col == 0) {
    return std::make_tuple(0,0);
  } else if (row <= kPuzzleSize - 1 && col < kPuzzleSize - 1) {
    // you're in the middle of a row but not the end of the column
    return std::make_tuple(row, col + 1);
  } else if (row < kPuzzleSize - 1 && col == kPuzzleSize - 1) {
    // you've reached the end of a row
    return std::make_tuple(row + 1, 0);
  } else {
    return std::make_tuple(0,0); // come back to this....
  }
}

bool Solver::CheckNorth(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckSouth(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckEast(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckWest(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckNorthWest(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckNorthEast(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckSouthWest(Puzzle a_single_puzzle, std::vector<char> characters) {

}
bool Solver::CheckSouthEast(Puzzle a_single_puzzle, std::vector<char> characters) {

}
} // namespace wordsearch