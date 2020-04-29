//
// Created by Jennifer Li on 4/21/20.
//

#include <wordsearch/puzzle.h>

namespace wordsearch {
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
    for (int column = 0; column < kPuzzleSize; column++) {
      puzzle_[row][column] = tolower(puzzle.at(char_counter));
      char_counter++;
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
      tolower(c);
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
  while (token != NULL)
  {
    // adds each word into the
    words_list.push_back(token);
    token = std::strtok(NULL, " ");
  }
}

// Allows the altering of the grid
void Puzzle::ChangeCharacter(int row, int col, char value) {
  puzzle_[row][col] = value;
}
// Checks for value in trie
bool Puzzle::Check(std::vector<char> values) {
  return words_trie_.check(values);
}
// Removes value in trie
void Puzzle::Remove(std::vector<char> values) {
  words_trie_.remove(values);
}

// checks if trie is empty
bool Puzzle::IsTrieEmpty() {
  // Check for every letter in the alphabet - if all of them are empty nodes
  // then return true
  bool IsEmpty = true;
  std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i',
                                'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  std::vector<char> letter;
  for (char c : alphabet) {
    letter.push_back(c);
    if (words_trie_.check(letter) == true) {
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
      grid[row][column] = tolower(puzzle.at(char_counter));
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
      tolower(c);
    }
    temp.add(word_vec);
    word_vec.clear();
  }
  words_trie = temp;
}





// Method for solving a puzzle has a vector of chars to keep track of characters
// found
bool Puzzle::Solve(Puzzle a_single_puzzle, std::vector<char> characters) {
  if (a_single_puzzle.IsTrieEmpty()) { // if all words have been found then success!
    return true;
  }
  // Consider 8 directions

  return false;
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
    return std::make_tuple(0,0); // come back to this....
  }
}
} // namespace wordsearch