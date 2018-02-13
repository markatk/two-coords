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

#include <vector>
#include <GL/glew.h>

twoCoords::Renderer::Renderer(twoCoords::Window *window) {
  _window = window;
  _screenUnitsX = 1;
  _screenUnitsY = 1;

  // create new program with sprite shaders
  std::vector<Shader> shaders;
  shaders.push_back(Shader(SPRITE_VERTEX_SHADER, GL_VERTEX_SHADER));
  shaders.push_back(Shader(SPRITE_FRAGMENT_SHADER, GL_FRAGMENT_SHADER));

  _spriteProgram = new ShaderProgram(shaders);

  // set open gl properties
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

twoCoords::Renderer::~Renderer() {
  delete _spriteProgram;
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

void twoCoords::Renderer::update() {
  renderEmptyScene();
}

twoCoords::Window *twoCoords::Renderer::window() const {
  return _window;
}

twoCoords::ShaderProgram *twoCoords::Renderer::shaderProgram() const {
  return _spriteProgram;
}

void twoCoords::Renderer::renderEmptyScene() const {
  // only clear buffer and fill with black color
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
