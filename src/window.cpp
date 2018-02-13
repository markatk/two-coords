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

#include "renderer.h"

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

  if (GLEW_VERSION_4_1 == false) {
    throw std::runtime_error("OpenGL 4.1 not available");
  }

  // register callbacks
  _sizeCallback = nullptr;
  _closeCallback = nullptr;
  _refreshCallback = nullptr;
  _focusCallback = nullptr;
  _iconifyCallback = nullptr;

  glfwSetWindowSizeCallback(_window, windowSizeCallback);
  glfwSetWindowCloseCallback(_window, windowCloseCallback);
  glfwSetWindowRefreshCallback(_window, windowRefreshCallback);
  glfwSetWindowFocusCallback(_window, windowFocusCallback);
  glfwSetWindowIconifyCallback(_window, windowIconifyCallback);

  _renderer = new twoCoords::Renderer(this);
}

twoCoords::Window::~Window() {
  glfwDestroyWindow(_window);
}

void twoCoords::Window::update() const {
  // render next frame
  _renderer->update();

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

void twoCoords::Window::setScreenUnits(int x, int y) {
  _renderer->setScreenUnits(x, y);
}

void twoCoords::Window::setSizeCallback(windowSizeCallback_t callback) {
  _sizeCallback = callback;
}

void twoCoords::Window::setCloseCallback(windowCloseCallback_t callback) {
  _closeCallback = callback;
}

void twoCoords::Window::setRefreshCallback(windowRefreshCallback_t callback) {
  _refreshCallback = callback;
}

void twoCoords::Window::setFocusCallback(windowFocusCallback_t callback) {
  _focusCallback = callback;
}

void twoCoords::Window::setIconifyCallback(windowIconifyCallback_t callback) {
  _iconifyCallback = callback;
}

twoCoords::Renderer *twoCoords::Window::renderer() const {
  return _renderer;
}

void twoCoords::Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
  Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_sizeCallback) {
		userPointer->_sizeCallback(userPointer, width, height);
	}
}

void twoCoords::Window::windowCloseCallback(GLFWwindow *window) {
  Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_closeCallback) {
		userPointer->_closeCallback(userPointer);
	}
}

void twoCoords::Window::windowRefreshCallback(GLFWwindow *window) {
  Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_refreshCallback) {
		userPointer->_refreshCallback(userPointer);
	}
}

void twoCoords::Window::windowFocusCallback(GLFWwindow *window, int focused) {
  Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_focusCallback) {
		userPointer->_focusCallback(userPointer, focused);
	}
}

void twoCoords::Window::windowIconifyCallback(GLFWwindow *window, int iconified) {
  Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_iconifyCallback) {
		userPointer->_iconifyCallback(userPointer, iconified);
	}
}
