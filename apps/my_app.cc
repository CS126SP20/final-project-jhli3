// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "wordsearch/parser.h"
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <mylibrary/fmt/core.h>

#include <cinder/app/App.h>

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::string;

namespace myapp {
const char kNormalFont[] = "Arial";

using cinder::app::KeyEvent;

MyApp::MyApp() {
  TestParser();
}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() {
  PrintSampleTest();
}

void MyApp::keyDown(KeyEvent event) { }

// Prints a given text
// Method from Snake game
void MyApp::PrintText(const string& text, const cinder::Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
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

// Just a method to test the formatting function of string with fmt
void MyApp::PrintSampleTest() {
  // Setting some variable to print the text
  const Color color = Color::white();
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  // sample text testing fmt
  //std::string message = fmt::format("The answer is {}", 42);
  std::string message = fmt::format("Don't {1}, be {0}", "happy", "worry");

  PrintText(message, color, size, center);
}

void MyApp::TestParser() {
  wordsearch::Parser parser;
  std::string file_name = "wordsearch.spf";
  parser.ParseFile(file_name);
}

}  // namespace myapp
