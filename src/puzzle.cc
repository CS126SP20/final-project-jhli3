//
// Created by Jennifer Li on 4/21/20.
//

#include <wordsearch/puzzle.h>

namespace wordsearch {
std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i',
                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
Puzzle::Puzzle() {

}

// Overloaded constructor
Puzzle::Puzzle(std::string& puzzle, std::string& words) {
  // load 2d array with values from puzzle string
  CreatePuzzleGrid(puzzle);
  // create trie of words
  CreateTrie(words);
}

// Fill 2d grid with letters of the puzzle
void Puzzle::CreatePuzzleGrid(std::string& puzzle) {
  // Keeps track of the character in the puzzle
  int char_counter = 0;
  // iterates through 2d array
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int col = 0; col < kPuzzleSize; col++) {
      puzzle_[row][col] = toupper(puzzle.at(char_counter));
      solution_[row][col] = toupper(puzzle.at(char_counter));
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
    for (char c : word_vec) {
      toupper(c);
    }
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
  while (token != nullptr)
  {
    // adds each word into the
    words_list.emplace_back(token);
    token = std::strtok(nullptr, " ");
  }
}

// checks if trie is empty
bool Puzzle::IsTrieEmpty() {
  // Check for every letter in the alphabet - if all of them are empty nodes
  // then return true
  bool IsEmpty = true;
  std::vector<char> letter;
  for (char c : alphabet) {
    letter.push_back(c);
    if (words_trie_.check(letter)) {
      IsEmpty = false; // trie can't be empty since there's a "word" in it
      break; // no need to continue looping if this is the case
    }
    letter.clear(); // clear the letter out
  }
  return IsEmpty;
}

// --------- Methods to help with testing ---------
void Puzzle::CreatePuzzleGrid(std::string& puzzle, char grid[kPuzzleSize][kPuzzleSize]) {
  // Keeps track of the character in the puzzle
  int char_counter = 0;
  // iterates through 2d array
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int column = 0; column < kPuzzleSize; column++) {
      grid[row][column] = toupper(puzzle.at(char_counter));
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
    for (char c : word_vec) {
      toupper(c);
    }
    temp.add(word_vec);
    word_vec.clear();
  }
  words_trie = temp;
}

void Puzzle::ChangeCharacter(int row, int col, char value) {
  solution_[row][col] = value;
}

char Puzzle::GetCharacter(int row, int col) {
  return solution_[row][col];
}

// --------- Methods for solving the puzzle  ---------

// Method for solving a puzzle has a vector of chars to keep track of characters
// found
bool Puzzle::Solve(Puzzle& a_single_puzzle, int row, int col) {
  if (a_single_puzzle.IsTrieEmpty()) { // if all words have been found then success!
    return true;
  }
  // Check if this first character is beginning of a word being sought
  if (a_single_puzzle.words_trie_.check({a_single_puzzle.puzzle_[row][col]})) {
    std::vector<char> characters;
    // Consider 8 directions for one square of the grid if one direction is true then run the same direction algorithm
    if (CheckNorth(a_single_puzzle, row - 1, col, characters)) { //if the word is found north
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckSouth(a_single_puzzle, row + 1, col, characters)) { //if the word is found south
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckEast(a_single_puzzle, row, col + 1, characters)) { //if the word is found east
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckWest(a_single_puzzle, row, col - 1, characters)) { //if the word is found west
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckNorthEast(a_single_puzzle, row - 1, col + 1, characters)) { //if the word is found northeast
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckNorthWest(a_single_puzzle, row - 1, col - 1, characters)) { //if the word is found northwest
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckSouthEast(a_single_puzzle, row + 1, col + 1, characters)) { //if the word is found southeast
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
    if (CheckSouthWest(a_single_puzzle, row + 1, col - 1, characters)) { //if the word is found southwest
      a_single_puzzle.words_trie_.remove(characters);
    }
    characters.clear();
  }

  // Move onto next square on grid
  std::tuple<int, int> next = FindNextCharacter(row, col);
  if (Solve(a_single_puzzle, std::get<0>(next), std::get<1>(next))) return true; // all words are eventually found
  return false; // a word wasn't found at some point
}
// method to find next box in grid
std::tuple<int, int> Puzzle::FindNextCharacter(int row, int col) {
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
    return std::make_tuple(-1,-1); // this means all squares on the grid have been checked
  }
}

void Puzzle::UndoRemoval(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
  a_single_puzzle.solution_[row][col] = characters.at(characters.size() - 1); // undo the addition of character
  characters.pop_back();
}

bool Puzzle::IsFullWord(Trie<char>& trie, std::vector<char>& word) {
  for (char letter : alphabet) {
    word.push_back(toupper(letter)); // adds letter
    if (trie.check(word)) { // checks if there's a potential word
      word.pop_back();
      return false; // if there's potential then it's not a full word yet
    }
    word.pop_back(); // removes letter and moves onto the next one
  }
  return true;
}

bool Puzzle::CheckNorth(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
  // Check validity of coordinate
  if (row < 0) return false; // when going up the row number decreases
  characters.push_back(a_single_puzzle.puzzle_[row][col]); // when checking words use the puzzle variable
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckNorth(a_single_puzzle, row - 1, col, characters)) { // Otherwise check if the continuation north will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}

bool Puzzle::CheckSouth(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (row >= kPuzzleSize) return false; // when going up the row number increases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckSouth(a_single_puzzle, row + 1, col, characters)) { // Otherwise check if the continuation south will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}

bool Puzzle::CheckEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (col >= kPuzzleSize) return false; // when going east the col number increases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckEast(a_single_puzzle, row, col + 1, characters)) { // Otherwise check if the continuation east will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}

bool Puzzle::CheckWest(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (col < 0) return false; // when going west the col number decreases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckWest(a_single_puzzle, row, col - 1, characters)) { // Otherwise check if the continuation west will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}
bool Puzzle::CheckNorthWest(Puzzle&a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (row < 0 || col < 0) return false; // when going NW the row number decreases and col decreases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckNorthWest(a_single_puzzle, row - 1, col -1, characters)) { // Otherwise check if the continuation nw will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}
bool Puzzle::CheckNorthEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (row < 0 || col >= kPuzzleSize) return false; // when going ne the row number decreases and col increases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckNorthEast(a_single_puzzle, row - 1, col + 1, characters)) { // Otherwise check if the continuation ne will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}
bool Puzzle::CheckSouthWest(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (row >= kPuzzleSize || col < 0) return false; // when going sw the row number increases and col decreases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckSouthWest(a_single_puzzle, row + 1, col - 1, characters)) { // Otherwise check if the continuation sw will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}
bool Puzzle::CheckSouthEast(Puzzle& a_single_puzzle, int row, int col, std::vector<char>& characters) {
// Check validity of coordinate
  if (row >= kPuzzleSize || col >= kPuzzleSize) return false; // when going se the row number increases and col increases
  characters.push_back(a_single_puzzle.puzzle_[row][col]);
  a_single_puzzle.solution_[row][col] = '.'; // temporarily removes the character
  if (a_single_puzzle.words_trie_.check(characters)) { // if the word exists in trie
    // At this point thus far the characters do belong in the trie and hold potential
    // to be a word being sought
    if (IsFullWord(a_single_puzzle.words_trie_, characters)) { // Check if word is full word
      return true;
    } else if (CheckSouthEast(a_single_puzzle, row + 1, col + 1, characters)) { // Otherwise check if the continuation se will find the word
      return true;
    }
    // at this point the word doesn't exist in the puzzle so undo the removal of the character
    UndoRemoval(a_single_puzzle, row, col, characters);
  }
  return false; // this triggers back tracking
}
} // namespace wordsearch