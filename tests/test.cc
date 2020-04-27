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
}

//TEST_CASE("Trie test", "[random]") {
//  Trie<char> trie;
//
//  trie.add({'a', 'p', 'p', 'l', 'e', 's'});
//  trie.add({'a', 'p', 'r', 'o', 'n'});
//  trie.add({'a', 'b', 'l', 'e'});
//  trie.add({'c', 'a', 'p'});
//  trie.add({'c', 'a', 'p', 'p', 'e', 'd'});
//
//  REQUIRE(trie.check({'a', 'p', 'p'}) == true);
//  REQUIRE(trie.check({'a', 'p', 'p', 'l', 'e'}) == true);
//  REQUIRE(trie.check({'a', 'b'}) == true);
//  REQUIRE(trie.check({'c', 'a', 'p', 'p', 'e'}) == true);
//
//  REQUIRE(trie.check({'p', 'e', 'd'}) == false);
//}
//
//TEST_CASE("CreateTrie test", "[random]") {
//  Trie<char> trie;
//  std::string words = "APPLES APRON ABLE CAP CAPPED";
//
//  wordsearch::Puzzle::CreateTrie(words, trie);
//
//  //REQUIRE(trie.check({'a', 'p', 'p'}) == true);
//  REQUIRE(trie.check({'a', 'p', 'p', 'l', 'e', 's'}) == true);
//  REQUIRE(trie.check({'a', 'b'}) == true);
//  REQUIRE(trie.check({'c', 'a', 'p', 'p', 'e'}) == true);
//
//  REQUIRE(trie.check({'p', 'e', 'd'}) == false);
//}
//
//TEST_CASE("CreateWordListVector test", "[random]") {
//  std::string words = "APPLES APRON";
//  std::vector<std::string> words_list;
//
//  wordsearch::Puzzle::CreateWordListVector(words, words_list);
//  std::cout << words_list.size();
//  REQUIRE(words_list.size() == 2);
//  REQUIRE(words_list.at(0) == "APPLES");
//  REQUIRE(words_list.at(1) == "APRON");
//}