// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

const int kWindowWidth = 800;
const int kWindowHeight = 800;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  // Prints text in cinder terminal
  void PrintText(const std::string& text, const cinder::Color& color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  // Wrapper function for simply printing text in terminal
  void Print(std::string text);
  // Creates puzzle from file and solves puzzle
  void RunSolver();
  // Draws puzzle in terminal
  void DrawPuzzle();
  // Draws solution in terminal
  void DrawSolution();
  // Draws word bank in terminal
  void DrawWordBank();

 private:
  std::string puzzle_;
  std::string solution_;
  bool IsValidFile_{};
  bool IsSolutionFound_{};
  bool ShowSolution_{};
  std::vector<std::string> words_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
