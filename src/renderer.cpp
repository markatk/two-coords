/**
 * Project: Two-Coords
 * File: src/renderer.cpp
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

#include "renderer.h"

#include "shader.h"
#include "spriteShader.h"
#include "shaderProgram.h"
#include "scene.h"
#include "sceneNode.h"
#include "sceneObject.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

// this function is used to sort the render nodes
bool compareLayerLower(const twoCoords::SceneNode *first, const twoCoords::SceneNode *second);

twoCoords::Renderer::Renderer() {
  _screenUnitsX = 1;
  _screenUnitsY = 1;

  // create new program with sprite shaders
  std::vector<Shader> shaders;
  shaders.push_back(Shader(SPRITE_VERTEX_SHADER, GL_VERTEX_SHADER));
  shaders.push_back(Shader(SPRITE_FRAGMENT_SHADER, GL_FRAGMENT_SHADER));

  _spriteProgram = std::make_shared<ShaderProgram>(shaders);

  // set open gl properties
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

twoCoords::Renderer::~Renderer() {

}

void twoCoords::Renderer::setScreenUnits(int x, int y) {
  _screenUnitsX = x;
  _screenUnitsY = y;
}

int twoCoords::Renderer::screenUnitsX() const {
  return _screenUnitsX;
}

int twoCoords::Renderer::screenUnitsY() const {
  return _screenUnitsY;
}

void twoCoords::Renderer::update(std::shared_ptr<Scene> scene) {
  if (scene == nullptr) {
    renderEmptyScene();
    return;
  }

  // clear buffer
  glClearColor(scene->backgroundColor().x, scene->backgroundColor().y, scene->backgroundColor().z, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // calculate camera projection
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(_screenUnitsX), static_cast<GLfloat>(_screenUnitsY), 0.0f, -100.0f, 0.1f);

  // clear render list
  _spriteNodes.clear();

  addNode(scene->rootNode());

  // sort lists by layer from low to high
  _spriteNodes.sort(compareLayerLower);

  // render sprite nodes with projection
  _spriteProgram->use();
  _spriteProgram->setUniform("projection", projection);

  for (auto it = _spriteNodes.begin(); it != _spriteNodes.end(); it++) {
    if ((*it)->isHidden()) {
      continue;
    }

    _spriteProgram->setUniform("model", (*it)->model());
    (*it)->render(_spriteProgram);
  }

  // release shader
  _spriteProgram->stopUsing();
}

std::shared_ptr<twoCoords::ShaderProgram> twoCoords::Renderer::shaderProgram() const {
  return _spriteProgram;
}

void twoCoords::Renderer::renderEmptyScene() const {
  // only clear buffer and fill with black color
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void twoCoords::Renderer::addNode(std::shared_ptr<SceneNode> node) {
  // add node itself
  if (std::dynamic_pointer_cast<SceneObject>(node) != nullptr) {
    _spriteNodes.push_back(node.get());
  }

  // add children
  for (auto it = node->children().begin(); it != node->children().end(); it++) {
    addNode(*it);
  }
}

bool compareLayerLower(const twoCoords::SceneNode *first, const twoCoords::SceneNode *second) {
  return first->layer() < second->layer();
}
