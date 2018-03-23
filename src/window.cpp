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
#include "sceneManager.h"
#include "scene.h"

#include <stdexcept>
#include <spdlog/spdlog.h>

twoCoords::Window::Window() {
  _window = nullptr;
  _sceneManager = nullptr;
  _renderer = nullptr;
}

twoCoords::Window::~Window() {
  glfwDestroyWindow(_window);
}

bool twoCoords::Window::create(int width, int height, std::string title, GLFWmonitor *monitor) {
  _window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
  if (_window == NULL) {
    spdlog::get("console")->error("glfwCreateWindow failed");
    return false;
  }

  // setup window
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);

  // disable v-sync
  glfwSwapInterval(0);

  // init glew
  if (glewInit() != GLEW_OK) {
    spdlog::get("console")->error("glewInit failed");
    return false;
  }

  auto console = spdlog::get("console");
  console->info(std::string("OpenGL version: ") + (const char *)glGetString(GL_VERSION));
  console->info(std::string("GLSL version: ") + (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  console->info(std::string("Vendor: ") + (const char *)glGetString(GL_VENDOR));
  console->info(std::string("Renderer: ") + (const char *)glGetString(GL_RENDERER));

  if (GLEW_VERSION_4_1 == false) {
    spdlog::get("console")->error("OpenGL 4.1 not available");
    return false;
  }

  _lastUpdateTime = glfwGetTime();
  _renderedFrames = 0;
  _lastFramesPerSecond = 0;

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

  glfwSetKeyCallback(_window, key_callback);
  glfwSetMouseButtonCallback(_window, mouseButton_callback);
  glfwSetCursorPosCallback(_window, cursorPosition_callback);
  glfwSetScrollCallback(_window, scroll_callback);

  // create objects
  _sceneManager = std::make_shared<SceneManager>(shared_from_this());
  _renderer = std::make_shared<Renderer>();

  return true;
}

void twoCoords::Window::update() {
  if (_sceneManager->isEmpty() == false) {
    _sceneManager->currentScene()->update();
  }

  // render next frame
  _renderer->update(_sceneManager->currentScene());

  // calculate the FPS
  double currentTime = glfwGetTime();
  _renderedFrames++;

  if (currentTime - _lastUpdateTime >= 1.0) {
    // reset FPS counter
    _lastFramesPerSecond = _renderedFrames;
    _renderedFrames = 0;
    _lastUpdateTime = currentTime;

    // spdlog::get("console")->info("FPS: " + std::to_string(_lastFramesPerSecond));
  }

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

std::shared_ptr<twoCoords::SceneManager> twoCoords::Window::sceneManager() const {
  return _sceneManager;
}

std::shared_ptr<twoCoords::Renderer> twoCoords::Window::renderer() const {
  return _renderer;
}

GLFWwindow *twoCoords::Window::windowHandle() const {
  return _window;
}

void twoCoords::Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
  auto userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_sizeCallback) {
		userPointer->_sizeCallback(userPointer->shared_from_this(), width, height);
	}
}

void twoCoords::Window::windowCloseCallback(GLFWwindow *window) {
  auto userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_closeCallback) {
		userPointer->_closeCallback(userPointer->shared_from_this());
	}
}

void twoCoords::Window::windowRefreshCallback(GLFWwindow *window) {
  auto userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_refreshCallback) {
		userPointer->_refreshCallback(userPointer->shared_from_this());
	}
}

void twoCoords::Window::windowFocusCallback(GLFWwindow *window, int focused) {
  auto userPointer= (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_focusCallback) {
		userPointer->_focusCallback(userPointer->shared_from_this(), focused);
	}
}

void twoCoords::Window::windowIconifyCallback(GLFWwindow *window, int iconified) {
  auto userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->_iconifyCallback) {
		userPointer->_iconifyCallback(userPointer->shared_from_this(), iconified);
	}
}

void twoCoords::Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->sceneManager()->isEmpty() == false) {
		userPointer->sceneManager()->currentScene()->key_callback(key, scancode, action, mods);
	}
}

void twoCoords::Window::mouseButton_callback(GLFWwindow *window, int button, int action, int mods) {
	Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->sceneManager()->isEmpty() == false) {
		userPointer->sceneManager()->currentScene()->mouseButton_callback(button, action, mods);
	}
}

void twoCoords::Window::cursorPosition_callback(GLFWwindow *window, double x, double y) {
	Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->sceneManager()->isEmpty() == false) {
		userPointer->sceneManager()->currentScene()->cursorPosition_callback(x, y);
	}
}

void twoCoords::Window::scroll_callback(GLFWwindow *window, double x, double y) {
	Window *userPointer = (Window *)glfwGetWindowUserPointer(window);
	if (userPointer->sceneManager()->isEmpty() == false) {
		userPointer->sceneManager()->currentScene()->scroll_callback(x, y);
	}
}
