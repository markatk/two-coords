/**
 * Project: Two-Coords
 * File: tests/window.cpp
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

#include <catch.hpp>
#include <memory>
#include <iostream>

#include "twoCoords.h"

TEST_CASE("Engine window", "[Two-Coords]") {
  REQUIRE(twoCoords::initialize() == true);
  std::shared_ptr<twoCoords::Window> window;

  SECTION("create a window") {
    window = std::make_shared<twoCoords::Window>();
    REQUIRE(window->create(640, 480, "Test window"));
    REQUIRE(window != nullptr);
  }

  SECTION("check window size") {
    window = std::make_shared<twoCoords::Window>();
    REQUIRE(window->create(800, 600, "Test window"));
    REQUIRE(window != nullptr);
    REQUIRE(window->width() == 800);
    REQUIRE(window->height() == 600);
  }

  twoCoords::deinitialize();
}
