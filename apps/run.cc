// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWindowWidth, kWindowHeight);
  settings->setTitle("Word Search Solver");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)

