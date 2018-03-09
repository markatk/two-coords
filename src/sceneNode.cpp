/**
 * Project: Two-Coords
 * File: src/sceneNode.cpp
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

#include "sceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

twoCoords::SceneNode::SceneNode(glm::vec2 position) {
  _position = position;
  _scale = glm::vec2(1.0f);
  _layer = 0;
  _rotation = 0.0f;
  _size = glm::vec2(0.0f);
  _hidden = false;
  _parent = nullptr;
}

twoCoords::SceneNode::~SceneNode() {

}

void twoCoords::SceneNode::render(std::shared_ptr<twoCoords::ShaderProgram> program) {

}

std::shared_ptr<twoCoords::SceneNode> twoCoords::SceneNode::parent() const {
  return _parent;
}

void twoCoords::SceneNode::setPosition(glm::vec2 position) {
  _position = position;
}

void twoCoords::SceneNode::setPosition(float x, float y) {
  _position.x = x;
  _position.y = y;
}

glm::vec2 twoCoords::SceneNode::position() const {
  return _position;
}

void twoCoords::SceneNode::setLayer(unsigned int layer) {
  _layer = layer;
}

unsigned int twoCoords::SceneNode::layer() const {
  return _layer;
}

void twoCoords::SceneNode::setScale(glm::vec2 scale) {
  _scale = scale;
}

void twoCoords::SceneNode::setScale(float x, float y) {
  _scale.x = x;
  _scale.y = y;
}

void twoCoords::SceneNode::setScale(float scale) {
  _scale.x = scale;
  _scale.y = scale;
}

glm::vec2 twoCoords::SceneNode::scale() const {
  return _scale;
}

void twoCoords::SceneNode::setRotation(float rotation) {
  _rotation = rotation;
}

float twoCoords::SceneNode::rotation() const {
  return _rotation;
}

void twoCoords::SceneNode::setHidden(bool hidden) {
  _hidden = hidden;
}

bool twoCoords::SceneNode::isHidden() const {
  return _hidden;
}

void twoCoords::SceneNode::add(std::shared_ptr<twoCoords::SceneNode> child) {
  _children.push_back(child);
  child->_parent = shared_from_this();
}

void twoCoords::SceneNode::remove(std::shared_ptr<twoCoords::SceneNode> child) {
  auto it = _children.begin();
  while (it != _children.end()) {
    if (*it == child) {
      it = _children.erase(it);
      child->_parent = nullptr;
    } else {
      it++;
    }
  }
}

const std::vector<std::shared_ptr<twoCoords::SceneNode>> &twoCoords::SceneNode::children() const {
  return _children;
}

bool twoCoords::SceneNode::hasChildren() const {
  return (_children.empty() == false);
}

glm::vec2 twoCoords::SceneNode::worldPosition() const {
  glm::vec2 position = _position;

  if (_parent != nullptr) {
    position += _parent->worldPosition();
  }

  return position;
}

glm::vec2 twoCoords::SceneNode::worldScale() const {
  glm::vec2 scale = _scale;

  if (_parent != nullptr) {
    scale += _parent->worldScale();
  }

  return scale;
}

glm::mat4 twoCoords::SceneNode::model() const {
  glm::mat4 model = modelForChild();
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, _layer));
  model = glm::scale(model, glm::vec3(_size, 1.0f));

  return model;
}

glm::mat4 twoCoords::SceneNode::modelForChild() const {
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(_position, 0.0f));
  model = glm::rotate(model, _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(_scale, 1.0f));

  if (_parent != nullptr) {
    model = _parent->modelForChild() * model;
  }

  return model;
}
