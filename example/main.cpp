/**
 * Project: Two-Coords
 * File: example/main.cpp
 * Created: 10.02.2018
 * Author: MarkAtk
 * 
 * MIT License
 * 
 * Copyright (c) 2018 Your Company
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "twoCoords.h"

#include <spdlog/spdlog.h>

void callback(twoCoords::Window *window, int width, int height) {
  spdlog::get("console")->info("Window changed " + std::to_string(width) + " " + std::to_string(height));
}

int main() {
  // initialize
  if (twoCoords::initialize() == false) {
    spdlog::get("console")->error("Unable to initialize Two-Coords");
    return EXIT_SUCCESS;
  }

  // create window
  twoCoords::Window *window;

  try {
    window = new twoCoords::Window(640, 480, "Two-Coords Example");
    window->setScreenUnits(800, 600);
    window->setSizeCallback(callback);
  } catch (std::exception &e) {
    spdlog::get("console")->error(e.what());
    return EXIT_FAILURE;
  }

  // main loop
  while (window->isOpen()) {
    window->update();
  }

  // cleanup
  delete window;

  twoCoords::deinitialize();
}
