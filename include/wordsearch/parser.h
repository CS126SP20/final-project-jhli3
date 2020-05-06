//
// Created by Jennifer Li on 4/21/20.
//

#ifndef FINALPROJECT_PARSER_H
#define FINALPROJECT_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "puzzle.h"

namespace wordsearch {
class Parser {
 private:
  // board size
  Puzzle NewPuzzle_;

  // Checks that file exists
  bool DoesFileExist(std::string& file_name);
  // Splits the text line by line and adds to a vector
  // Vector should only have 3 elements: header, puzzle, words
  void SplitTextLines(std::string& file_name, std::vector<std::string>& lines);
  // Checks if file is valid
  // A file is valid if it has a header, has a 15 x 15 puzzle,
  // and max 30 words (only 4 words can have the max length of 15)
  bool IsFileValid(std::vector<std::string>& lines);
  // Checks that puzzles are of valid format
  // everything is of correct length and amount
  // all characters are letters, capitalization does not matter
  // words are separated by spaces
  bool IsPuzzleValid(std::string& wordsearch, std::string& words);
  // Checks that a string is only filled with characters of the alphabet
  bool IsAllLetters(std::string& line);
  // Checks that word list is valid
  bool IsWordListValid(std::vector<std::string>& words);

 public:
  // Runs the parsing of the file
  // Returns true if file is parseable, false otherwise
  bool ParseFile(std::string& file_name);
  // For testing purposes
  // Runs the parsing of the file
  void ParseFileTester(std::string& file_name, std::ostream& cout = std::cout);
  // Returns a reference to the newly created puzzle
  Puzzle& GetPuzzle();
};
}  // namespace wordsearch

#endif  // FINALPROJECT_PARSER_H
