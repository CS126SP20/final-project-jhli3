//
// Created by Jennifer Li on 4/21/20.
//

#include <wordsearch/parser.h>

namespace wordsearch {
// constant header
std::string const kHeader = "#spr1.0";
int const kFileSize = 3;
int const kCharacterSize = 1;

// Runs the parsing of the file
void Parser::ParseFile(std::string& file_name) {
  // Checks that file exists
  if (DoesFileExist(file_name)) { // if it doesn't exist a message will be print
    std::vector<std::string> file_lines; // create vector holding lines in file
    SplitTextLines(file_name, file_lines); // split lines and add to vector

    // Using this vector check that file is holding valid contents
    if (IsFileValid(file_lines)) {
      // create a puzzle object
      std::cout << "Puzzle created";
    } else {
      std::cout << "This is an invalid file.";
    }
  }
}
// Checks that file exists
// code below derived in part from:
// https://stackoverflow.com/questions/1647557/ifstream-how-to-tell-if-specified-file-doesnt-exist
bool Parser::DoesFileExist(std::string& file_name) {
    std::ifstream my_file(file_name.c_str());
    // Check to make sure that file opens
    if (my_file) {
      return true;
    } else {
      // If image file doesn't properly open
      std::cout << "Failed to open file " << file_name << std::endl;
      return false;
    }
//  std::ifstream file_stream(file_name.c_str());
//  if (file_stream.fail()) {
//    std::cout << "This file does not exist";
//    return false;
//  }
//  return true;
}

// Splits the text line by line and adds to a vector
// Vector should only have 3 elements: header, puzzle, words
void Parser::SplitTextLines(std::string& file_name, std::vector<std::string>& lines) {
  std::ifstream my_file(file_name.c_str());
  // Check that stream is still good
  if (my_file) {
    std::string line;
    while (getline(my_file, line)){ // while there are still lines in file
      lines.push_back(line); // add line to vector
      line.clear(); // clear the line
    }
  }
  std::cout << "There's something wrong with the stream";
}
// Checks if file is valid
// A file is valid if it has a header, has a 15 x 15 puzzle,
// and max 30 words
bool Parser::IsFileValid(std::vector<std::string>& lines) {
  if (lines.size() != kFileSize) { // files contains the wrong contents
    return false;
  } else if (lines.at(0).compare(kHeader) != 0) { // files header does not match
    return false;
  } else if (!IsPuzzleValid(lines.at(1), lines.at(2))) {
    // is the puzzle included a valid puzzle
    return false;
  }
  return true;
}
// Checks that puzzles are of valid format
// everything is of correct length and amount
// all characters are letters, capitalization does not matter
// words are separated by spaces
// code for splitting a sentence based on the spaces derived from below:
// https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
bool Parser::IsPuzzleValid(std::string& wordsearch, std::string& words) {
  if (wordsearch.size() != kPuzzleSize * kPuzzleSize) { // puzzle of wrong size
    return false;
  } else if (!IsAllLetters(wordsearch)) { // checks that puzzle is only letters
    return false;
  }
  // split words list into individual words
  // convert list of words into a char array
  char char_of_words[words.size() + 1];
  strcpy(char_of_words, words.c_str());
  // Returns first token
  char *token = std::strtok(char_of_words, " ");
  std::vector<std::string> words_list;
  // Keep printing tokens while one of the
  // delimiters present in char_of_words[].
  while (token != NULL)
  {
    // adds each word into the
    words_list.push_back(token);
    token = std::strtok(NULL, " ");
  }
  if (!IsWordListValid(words_list)) {
    return false;
  }
  return true;
}

// Checks that a string is only filled with characters of the alphabet
bool Parser::IsAllLetters(std::string& line) {
  for (char c : line) {
    // if the character isn't in the upper case range (65 - 90) or the lower
    // case range (97 - 122)
    if (!(c > 64 && c < 91) || !(c > 96 && c < 123)) {
      return false;
    }
  }
  return true;
}

bool Parser::IsWordListValid(std::vector<std::string> words) {
  // if there are no words or too many words
  if (words.size() == 0 || words.size() > 30) {
    return false;
  }
  for (std::string word : words) {
    if (!IsAllLetters(word)) {  // checks that each word is made of letters
      return false;
    } else if (word.size() == kCharacterSize || word.size() > kPuzzleSize) {
      // word cannot be 1 letter or more than puzzle size
      return false;
    }
    return true;
  }
}
} // namespace wordsearch