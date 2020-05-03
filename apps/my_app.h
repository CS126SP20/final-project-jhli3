// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>


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
  void PrintSampleTest();
  void TestParser();
  void TestSolver();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
