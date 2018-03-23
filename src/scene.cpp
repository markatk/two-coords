/**
 * Project: Two-Coords
 * File: src/scene.cpp
 * Created: 13.02.2018
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

#include "scene.h"

#include "sceneNode.h"
#include "window.h"
#include "resourceManager.h"

twoCoords::Scene::Scene(glm::vec3 backgroundColor) {
  _backgroundColor = backgroundColor;
  _rootNode = std::make_shared<SceneNode>();
  _resourceManager = std::make_shared<ResourceManager>();
}

twoCoords::Scene::~Scene() {
  
}

void twoCoords::Scene::update() {

}

void twoCoords::Scene::enter() {

}

void twoCoords::Scene::exit() {

}

void twoCoords::Scene::setBackgroundColor(glm::vec3 color) {
  _backgroundColor = color;
}

void twoCoords::Scene::setBackgroundColor(float red, float green, float blue) {
  _backgroundColor.x = red;
  _backgroundColor.y = green;
  _backgroundColor.z = blue;
}

glm::vec3 twoCoords::Scene::backgroundColor() const {
  return _backgroundColor;
}

int twoCoords::Scene::key(int key) const {
  auto window = _window.lock();
  if (window == nullptr) {
    return -1;
  }

  return glfwGetKey(window->windowHandle(), key);
}

int twoCoords::Scene::mouseButton(int button) const {
  auto window = _window.lock();
  if (window == nullptr) {
    return -1;
  }

  return glfwGetMouseButton(window->windowHandle(), button);
}

void twoCoords::Scene::key_callback(int key, int scancode, int action, int mods) {

}

void twoCoords::Scene::mouseButton_callback(int button, int action, int mods) {

}

void twoCoords::Scene::cursorPosition_callback(double x, double y) {

}

void twoCoords::Scene::scroll_callback(double x, double y) {
  
}

std::shared_ptr<twoCoords::SceneNode> twoCoords::Scene::rootNode() const {
  return _rootNode;
}

std::shared_ptr<twoCoords::ResourceManager> twoCoords::Scene::resourceManager() const {
  return _resourceManager;
}

void twoCoords::Scene::setWindow(std::shared_ptr<Window> window) {
  _window = window;
}

std::shared_ptr<twoCoords::Window> twoCoords::Scene::window() const {
  return _window.lock();
}
