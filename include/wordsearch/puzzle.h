//
// Created by Jennifer Li on 4/21/20.
//

#ifndef FINALPROJECT_PUZZLE_H
#define FINALPROJECT_PUZZLE_H

#include <string>
#include <vector>

#include "solver.h"
constexpr size_t kPuzzleSize = 15;

namespace wordsearch {
class Puzzle {
 private:
  char puzzle_ [kPuzzleSize][kPuzzleSize];

 public:
  // Default constructor
  Puzzle();
  // Overloaded constructor
  explicit Puzzle(std::string& puzzle, std::string& words);
  // Solve the puzzle
  void Solve();
};
} // namespace wordsearch
#endif  // FINALPROJECT_PUZZLE_H
