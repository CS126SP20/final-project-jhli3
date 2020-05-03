//
// Created by Jennifer Li on 4/21/20.
//

#include <wordsearch/parser.h>

using std::cout;

namespace wordsearch {
// constant header
std::string const kHeader = "#spf1.0";
int const kFileSize = 3;
int const kCharacterSize = 1;

// Runs the parsing of the file
Puzzle Parser::ParseFile(std::string& file_name) {
  // Checks that file exists
  if (DoesFileExist(
          file_name)) {  // if it doesn't exist a message will be print
    std::vector<std::string> file_lines;  // create vector holding lines in file
    SplitTextLines(file_name, file_lines);  // split lines and add to vector

    // Using this vector check that file is holding valid contents
    if (IsFileValid(file_lines)) {
      // create a puzzle object
      cout << "Puzzle created" << std::endl;
      return Puzzle(file_lines.at(1), file_lines.at(2));
    } else {
      cout << "This is an invalid file";
      return Puzzle();
    }
  } else {
    cout << "This is an invalid file";
    return Puzzle();
  }
}
// Checks that file exists
// code below derived in part from:
// https://stackoverflow.com/questions/1647557/ifstream-how-to-tell-if-specified-file-doesnt-exist
bool Parser::DoesFileExist(std::string& file_name) {
    std::ifstream my_file;
    my_file.open(file_name);
    // Check to make sure that file opens
    if (my_file.fail()) {
      cout << "Failed to open file " << file_name << std::endl;
      return false;
    } else {
      cout << "Opened file " << file_name << std::endl;
      return true;
    }
}

// Splits the text line by line and adds to a vector
// Vector should only have 3 elements: header, puzzle, words
void Parser::SplitTextLines(std::string& file_name, std::vector<std::string>& lines) {
  std::ifstream my_file;
  my_file.open(file_name);
  std::string line;
    while (getline(my_file, line)){ // while there are still lines in file
    lines.push_back(line); // add line to vector
    line.clear(); // clear the line
  }
  //std::cout << "There's something wrong with the stream";
}
// Checks if file is valid
// A file is valid if it has a header, has a 15 x 15 puzzle,
// and max 30 words
bool Parser::IsFileValid(std::vector<std::string>& lines) {
  if (lines.size() != kFileSize) { // files contains the wrong contents
    cout << "Wrong number of lines";
    return false;
  } else if (lines.at(0) != kHeader) { // files header does not match
    cout << "Wrong header";
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
    cout << "Wrong puzzle size of " << wordsearch.size();
    return false;
  } else if (!IsAllLetters(wordsearch)) { // checks that puzzle is only letters
    cout << "Puzzle isn't all letters";
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
  while (token != nullptr)
  {
    // adds each word into the
    words_list.emplace_back(token);
    token = std::strtok(nullptr, " ");
  }
  //cout << "Word list size " << words_list.size() << std::endl;
  if (!IsWordListValid(words_list)) { // passes word list to check for validity
    cout << "A word isn't only letters";
    return false;
  }
  return true;
}

// Checks that a string is only filled with characters of the alphabet
bool Parser::IsAllLetters(std::string& line) {
  for (char c : line) {
    // if the character isn't in the upper case range (65 - 90) or the lower
    // case range (97 - 122)
    if (!(c >= 65 && c <= 90) && !(c >= 97 && c <= 122)) {
      return false;
    }
  }
  return true;
}

bool Parser::IsWordListValid(std::vector<std::string>& words) {
  // if there are no words or too many words
  if (words.empty() || words.size() > 30) {
    cout << "Invalid number of words";
    return false;
  }
  // Goes through each word in word list
  for (std::string word : words) {
    if (word.size() == kCharacterSize || word.size() > kPuzzleSize) {
      // word cannot be 1 letter or more than puzzle size
      cout << "Word of improper length";
      return false;
    } else if (!IsAllLetters(word)) {  // checks that each word is made of letters
      cout << "Word with invalid character";
      return false;
    }
  }
  return true;
}

// ------------- Methods for testing -------------
// Runs the parsing of the file
// Code derived from:
// https://stackoverflow.com/questions/40297782/c-unit-testing-check-output-is-correct
void Parser::ParseFileTester(std::string& file_name, std::ostream& cout) {
  // Checks that file exists
  if (DoesFileExist(
      file_name)) {  // if it doesn't exist a message will be print
    std::vector<std::string> file_lines;  // create vector holding lines in file
    SplitTextLines(file_name, file_lines);  // split lines and add to vector

    // Using this vector check that file is holding valid contents
    if (IsFileValid(file_lines)) {
      // create a puzzle object
      Puzzle puzzle(file_lines.at(1), file_lines.at(2));
      cout << "Puzzle created";
    } else {
      cout << "This is an invalid file";
    }
  } else {
    cout << "This is an invalid file";
  }
}
} // namespace wordsearch