/**
 * Project: Two-Coords
 * File: src/window.cpp
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

#include "window.h"

#include <stdexcept>
#include <spdlog/spdlog.h>

twoCoords::Window::Window(int width, int height, std::string title, GLFWmonitor *monitor) {
  _window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
  if (_window == NULL) {
    throw std::runtime_error("glfwCreateWindow failed");
  }

  // setup window
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);

  // init glew
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glewInit failed");
  }

  auto console = spdlog::get("console");
  console->info(std::string("OpenGL version: ") + (const char *)glGetString(GL_VERSION));
  console->info(std::string("GLSL version: ") + (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  console->info(std::string("Vendor: ") + (const char *)glGetString(GL_VENDOR));
  console->info(std::string("Renderer: ") + (const char *)glGetString(GL_RENDERER));

  if (GLEW_VERSION_4_5 == false) {
    throw std::runtime_error("OpenGL 4.5 not available");
  }

  // register callbacks
  glfwSetWindowSizeCallback(_window, windowSizeCallback);
  glfwSetWindowCloseCallback(_window, windowCloseCallback);
  glfwSetWindowRefreshCallback(_window, windowRefreshCallback);
  glfwSetWindowFocusCallback(_window, windowFocusCallback);
  glfwSetWindowIconifyCallback(_window, windowIconifyCallback);
}

twoCoords::Window::~Window() {
  glfwDestroyWindow(_window);
}

void twoCoords::Window::update() const {
  // render
  glClear(GL_COLOR_BUFFER_BIT);

  // update window itself
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void twoCoords::Window::close() {
  glfwSetWindowShouldClose(_window, GL_TRUE);
}

bool twoCoords::Window::isOpen() const {
  return (glfwWindowShouldClose(_window) == false);
}

int twoCoords::Window::width() const {
  int width;
  glfwGetWindowSize(_window, &width, 0);
  return width;
}

int twoCoords::Window::height() const {
  int height;
  glfwGetWindowSize(_window, 0, &height);
  return height;
}

void twoCoords::Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
  
}

void twoCoords::Window::windowCloseCallback(GLFWwindow *window) {

}

void twoCoords::Window::windowRefreshCallback(GLFWwindow *window) {

}

void twoCoords::Window::windowFocusCallback(GLFWwindow *window, int focused) {

}

void twoCoords::Window::windowIconifyCallback(GLFWwindow *window, int iconified) {

}
