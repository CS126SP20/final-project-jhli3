// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/fmt/core.h>

#include "wordsearch/parser.h"

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::string;

namespace myapp {
// Monospaced san serif font for easy readability
const char kNormalFont[] = "Helvetica";
std::string file_name_ =
    "/Users/white/Cinder/my-projects/final-project-jhli3/data/"
    "wordsearch3.spf";

using cinder::app::KeyEvent;

MyApp::MyApp() {
  IsValidFile_ = false;
  IsSolutionFound_ = false;
  ShowSolution_ = false;
}

void MyApp::setup() {
  RunSolver();            // Run set up with puzzle and solve
  ShowSolution_ = false;  // Default show puzzle
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::clear();
  std::string error_message; // error message for when something goes wrong
  if (!IsValidFile_) {  // if file is invalid
    error_message = fmt::format("Error: {}", "Invalid puzzle file");
    Print(error_message);
  } else if (IsSolutionFound_) {  // if a solution is found display it
    if (ShowSolution_) {          // If toggled draw solution grid
      DrawSolution();
    } else {
      DrawPuzzle();
    }
    DrawWordBank();
  } else {  // display error message that solution wasn't found
    error_message = fmt::format("Error: {}", "Solution not found");
    Print(error_message);
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_RETURN: {
      // if you're on puzzle, pressing return will show solution
      // if you're on solution, pressing return will revert back to puzzle
      ShowSolution_ = !ShowSolution_;
    }
  }
}

// Prints a given text
// Method from Snake game
void MyApp::PrintText(const string& text, const cinder::Color& color,
                      const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);
  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(kNormalFont, 20))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

// Wrapper method for printing error messages
void MyApp::Print(const std::string& text) {
  // Setting some variable to print the text
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  PrintText(text, color, size, center);
}

// Formatting for drawing puzzle grid
void MyApp::DrawPuzzle() {
  // Set up default variables to pass on later
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {600, 50};
  const Color white = Color::white();

  int counter = 0;
  size_t x_placement = 0;
  size_t y_placement = 0;
  std::string letter;
  // Iterate through every letter and draw out a grid
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int col = 0; col < kPuzzleSize; col++) {
      letter += puzzle_.at(counter);
      PrintText(letter, white, size,
                {center.x - 250 + (x_placement)*35,
                 center.y - 320 + (y_placement)*35});
      x_placement++;
      counter++;
      letter.clear();
    }
    x_placement = 0;
    y_placement++;
  }
}

// Formatting for drawing solution grid
void MyApp::DrawSolution() {
  // Set up default variables to pass on later
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {600, 50};
  const Color white = Color::white();
  const Color red = {1, 0, 0};  // for found words
  Color color;

  int counter = 0;
  size_t x_placement = 0;
  size_t y_placement = 0;
  std::string letter;
  // Iterate through every letter and draw out a grid
  for (int row = 0; row < kPuzzleSize; row++) {
    for (int col = 0; col < kPuzzleSize; col++) {
      if (puzzle_.at(counter) != solution_.at(counter)) {
        // if solution holds a different character then color this letter red
        color = red;
      } else {
        color = white;
      }
      letter += puzzle_.at(counter);
      PrintText(letter, color, size,
                {center.x - 250 + (x_placement)*35,
                 center.y - 320 + (y_placement)*35});
      x_placement++;
      counter++;
      letter.clear();
    }
    x_placement = 0;
    y_placement++;
  }
}

// Formatting for drawing word bank
void MyApp::DrawWordBank() {
  // Set up default variables to pass on later
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {800, 50};
  const Color white = Color::white();

  int _x = center.x - 250;
  int _y = center.y + 225;

  // Iterate through words in vector and print out into columns
  for (std::string word : words_) {
    PrintText(word, white, size, {_x, _y});
    _y += 35;
    if (_y > kWindowHeight - 20) {
      _y = center.y + 225;
      _x += kPuzzleSize + 100;
    }
  }
}

// Create and Solve wordsearch
void MyApp::RunSolver() {
  wordsearch::Parser parser;
  if (parser.ParseFile(file_name_)) {  // if file parsing is sucessful
    IsValidFile_ = true;
    wordsearch::Puzzle my_puzzle = parser.GetPuzzle();  // create puzzle
    if (my_puzzle.Solve(
            my_puzzle)) {  // if puzzle is solveable set up puzzle and solution
      IsSolutionFound_ = true;
      // Set variables based on puzzle solving completion
      puzzle_ = my_puzzle.GetPuzzle();
      solution_ = my_puzzle.GetSolution();
      words_ = my_puzzle.GetWordsVector();
    }
  }
}
}  // namespace myapp
