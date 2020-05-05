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
  void PrintText(const std::string& text, const cinder::Color& color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  void TestSolver();
  void Print(std::string text);
  void DrawPuzzle();
  void DrawSolution();
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
