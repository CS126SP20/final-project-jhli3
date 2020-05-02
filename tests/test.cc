// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <catch2/catch.hpp>

#include "trie/trie.h"
#include "wordsearch/parser.h"

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Parser Test", "[parser]") {
  wordsearch::Parser parser; // create parser object
  std::ostringstream ss; // create string stream to catch output

   SECTION("No header") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/noheader.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("No puzzle 1") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/nopuzzle.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
  }

  SECTION("No puzzle 2") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/nopuzzle2.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
  }

  SECTION("Puzzle too long") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/puzzletoolong.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("Puzzle too short") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/puzzletooshort.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("Puzzle upper case") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/puzzleallupper.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "Puzzle created");
   }

  SECTION("Puzzle lower case") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/puzzlealllower.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "Puzzle created");
   }

  SECTION("Puzzle invalid character") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/puzzlewithinvalidcharacter.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("No word list") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/nowordslist.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("Too many words") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/toomanywords.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("Words uppercase") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/wordsallupper.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "Puzzle created");
   }

  SECTION("Words lowercase") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/wordsalllower.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "Puzzle created");
   }

  SECTION("A word too long") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/wordtoolong.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("A word too short (1 letter)") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/wordtooshort.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("Word with invalid symbol") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/wordwithinvalidsymbol.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
   }

  SECTION("File does not exist") {
    std::string file_name = "/Users/white/Cinder/my-projects/final-project-jhli3/tests/data/example.spf";
    parser.ParseFileTester(file_name, ss);
    REQUIRE(ss.str() == "This is an invalid file");
  }
}

TEST_CASE("CreateWordListVector test", "[puzzle]") {
  std::string words = "APPLES APRON";
  std::vector<std::string> words_list;

  wordsearch::Puzzle::CreateWordListVector(words, words_list);
  REQUIRE(words_list.size() == 2);
  REQUIRE(words_list.at(0) == "APPLES");
  REQUIRE(words_list.at(1) == "APRON");
}

// This test is help figure out how the trie template downloaded worked
TEST_CASE("Trie test", "[trie]") {
  Trie<char> trie; // Create trie of chars

  // add words to the trie
  trie.add({'a', 'p', 'p', 'l', 'e', 's'});
  trie.add({'a', 'p', 'r', 'o', 'n'});
  trie.add({'a', 'b', 'l', 'e'});
  trie.add({'c', 'a', 'p'});
  trie.add({'c', 'a', 'p', 'p', 'e', 'd'});

  // check/search for certain words in the trie
  REQUIRE(trie.check({'a', 'p', 'p'}) == true);
  REQUIRE(trie.check({'a', 'p', 'p', 'l', 'e'}) == true);
  REQUIRE(trie.check({'a', 'b'}) == true);
  REQUIRE(trie.check({'c', 'a', 'p', 'p', 'e'}) == true);

  // While this combination of symbols exists within the trie, it is not
  // a word that can be retrieved from the trie hierarchy
  REQUIRE(trie.check({'p', 'e', 'd'}) == false);
}

// Test my own CreateTrie method
TEST_CASE("CreateTrie test", "[puzzle], [trie]") {
  Trie<char> trie; // Create trie of chars
  std::string words = "apples apron able cap capped"; // Create string of words

  wordsearch::Puzzle::CreateTrie(words, trie); // Fill trie with words from string

  // Check that these words exist within the trie
  REQUIRE(trie.check({'a', 'p', 'p'}) == true); // implicitly formed word
  REQUIRE(trie.check({'a', 'p', 'p', 'l', 'e', 's'}) == true); // explicitly formed word
  REQUIRE(trie.check({'a', 'b'}) == true); // implicitly formed word
  REQUIRE(trie.check({'c', 'a', 'p', 'p', 'e'}) == true); // explicitly formed word

  // exists in the interior structure but not it's own independent word
  REQUIRE(trie.check({'p', 'e', 'd'}) == false);
}

TEST_CASE("CreatePuzzle test", "[puzzle]") {
  char grid [kPuzzleSize][kPuzzleSize];
  std::string puzzle_string =
      "EKOMOORHSUMEGHWHLBKDKKUFHESOXFLNPRTUSGMAWUPDGWSIPVLAHAICOBBHDBPVAAXIQXOHTNFHZPTOPVZHNAVOIYJKUUGVRYRFRVQVSFBTMRTVEEACLCYIXNUWIMORPWASHRKAGFRTRGVUOCYOYZNOCICEPAOWUBVBKZHLEAAJTWNNRZLBMWMGFUREUYJLMWYWXCATUUUDRYIQUBWPIEQIJOAQEBZVS";
  char correct_grid [kPuzzleSize][kPuzzleSize] =
      {{'E', 'K', 'O', 'M', 'O', 'O', 'R', 'H', 'S', 'U', 'M', 'E', 'G', 'H', 'W'},
       {'H', 'L', 'B', 'K', 'D', 'K', 'K', 'U', 'F', 'H', 'E', 'S', 'O', 'X', 'F'},
       {'L', 'N', 'P', 'R', 'T', 'U', 'S', 'G', 'M', 'A', 'W', 'U', 'P', 'D', 'G'},
       {'W', 'S', 'I', 'P', 'V', 'L', 'A', 'H', 'A', 'I', 'C', 'O', 'B', 'B', 'H'},
       {'D', 'B', 'P', 'V', 'A', 'A', 'X', 'I', 'Q', 'X', 'O', 'H', 'T', 'N', 'F'},
       {'H', 'Z', 'P', 'T', 'O', 'P', 'V', 'Z', 'H', 'N', 'A', 'V', 'O', 'I', 'Y'},
       {'J', 'K', 'U', 'U', 'G', 'V', 'R', 'Y', 'R', 'F', 'R', 'V', 'Q', 'V', 'S'},
       {'F', 'B', 'T', 'M', 'R', 'T', 'V', 'E', 'E', 'A', 'C', 'L', 'C', 'Y', 'I'},
       {'X', 'N', 'U', 'W', 'I', 'M', 'O', 'R', 'P', 'W', 'A', 'S', 'H', 'R', 'K'},
       {'A', 'G', 'F', 'R', 'T', 'R', 'G', 'V', 'U', 'O', 'C', 'Y', 'O', 'Y', 'Z'},
       {'N', 'O', 'C', 'I', 'C', 'E', 'P', 'A', 'O', 'W', 'U', 'B', 'V', 'B', 'K'},
       {'Z', 'H', 'L', 'E', 'A', 'A', 'J', 'T', 'W', 'N', 'N', 'R', 'Z', 'L', 'B'},
       {'M', 'W', 'M', 'G', 'F', 'U', 'R', 'E', 'U', 'Y', 'J', 'L', 'M', 'W', 'Y'},
       {'W', 'X', 'C', 'A', 'T', 'U', 'U', 'U', 'D', 'R', 'Y', 'I', 'Q', 'U', 'B'},
       {'W', 'P', 'I', 'E', 'Q', 'I', 'J', 'O', 'A', 'Q', 'E', 'B', 'Z', 'V', 'S'}};
  wordsearch::Puzzle::CreatePuzzleGrid(puzzle_string, grid);
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int col = 0; col < kPuzzleSize; col++) {
      REQUIRE(grid[row][col] == correct_grid[row][col]);
    }
  }
}

TEST_CASE("IsFullWord test", "[direction][trie]") {
  Trie<char> trie; // Create trie of chars

  // add words to the trie
  trie.add({'a', 'p', 'p', 'l', 'e', 's'});
  trie.add({'a', 'p', 'r', 'o', 'n'});
  trie.add({'a', 'b', 'l', 'e'});
  trie.add({'c', 'a', 'p'});
  trie.add({'c', 'a', 'p', 'p', 'e', 'd'});

  // This is a full word
  std::vector<char> full_word{'a', 'p', 'p', 'l', 'e', 's'};
  // This is not a full word
  std::vector<char> partial_word{'a', 'p', 'p', 'l', 'e'};

  wordsearch::Puzzle puzzle;

  REQUIRE(puzzle.IsFullWord(trie, full_word) == true);
  REQUIRE_FALSE(puzzle.IsFullWord(trie, partial_word));
}

TEST_CASE("RemovesCharacter test", "[direction][grid]") {
  std::string puzzle_string =
      "EKOMOORHSUMEGHW"
      "HLBKDKKUFHESOXF"
      "LNPRTUSGMAWUPDG"
      "WSIPVLAHAICOBBH"
      "BBPVAAXIQXOHTNF"
      "UZPTOPVZHNAVOIY"
      "GKUUGVRYRFRVQVS"
      "FBTMRTVEEACLCYI"
      "XNUWIMORPWASHRK"
      "AGFRTRGVUOCYOYZ"
      "NOCICEPAOWUBVBK"
      "ZHLEAAJTWNNRZLB"
      "MWMGFUREUYJLMWY"
      "WXCATUUUDRYIQUB"
      "WPIEQIJOAQEBZVS";
  std::string words = "BUG";
  wordsearch::Puzzle puzzle(puzzle_string, words);
  puzzle.ChangeCharacter(4, 0, '.'); // manually remove a value
  REQUIRE(puzzle.GetCharacter(4,0) == '.'); // check that it's been properly removed

  std::vector<char> word {'A','B'};
  puzzle.UndoRemoval(puzzle, 4, 0, word);
  REQUIRE(puzzle.GetCharacter(4,0) == 'B'); // Check that character has been restored
  REQUIRE(word.size() == 1); // Check that character is no longer in vector
}

TEST_CASE("Direction checks tests", "[direction]") {
  std::string puzzle_string =
      "EKOMOORHSUMEGHW"
      "HLBKDKKUFHESOXF"
      "LNPRTUSGMAWUPDG"
      "WSIPVLAHAICOBBH"
      "BBPVAAXIQXOHTNF"
      "UZPTOPVZHNAVOIY"
      "GKUUGVRYRFRVQVS"
      "FBTMRTVEEACLCYI"
      "XNUWIMORPWASHRK"
      "AGFRTRGVUOCYOYZ"
      "NOCICEPAOWUBVBK"
      "ZHLEAAJTWNNRZLB"
      "MWMGFUREUYJLMWY"
      "WXCATUUUDRYIQUB"
      "WPIEQIJOAQEBZVS";
  std::string words = "BUG";
  std::vector<char> characters;
  wordsearch::Puzzle puzzle(puzzle_string, words);
  REQUIRE(puzzle.CheckNorth(puzzle, 4, 0, characters) == true);
}
