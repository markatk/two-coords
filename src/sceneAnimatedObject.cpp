/**
 * Project: Two-Coords
 * File: src/sceneAnimatedObject.cpp
 * Created: 16.04.2018
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

#include "sceneAnimatedObject.h"

#include "shaderProgram.h"
#include "textureMap.h"

twoCoords::SceneAnimatedObject::SceneAnimatedObject(std::shared_ptr<TextureMap> textureMap, glm::vec2 position) : SceneObject(nullptr, position) {
    _frame = 0;
    _animation = 0;
    _vao = 0;
    _vbo = 0;

    setTextureMap(textureMap);
}

twoCoords::SceneAnimatedObject::~SceneAnimatedObject() {

}

void twoCoords::SceneAnimatedObject::render(std::shared_ptr<ShaderProgram> program) {
    auto textureMap = _textureMap.lock();
    if (textureMap == nullptr) {
        return;
    }

    program->setUniform("model", model());

    // connect attributes
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(program->attrib("vert"));
    glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(program->attrib("vertTexCoord"));
	glVertexAttribPointer(program->attrib("vertTexCoord"), 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureMap->object());
    program->setUniform("tex", 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void twoCoords::SceneAnimatedObject::setTextureMap(std::shared_ptr<TextureMap> textureMap) {
    _textureMap = textureMap;

    _size = glm::vec2(textureMap->tileWidth(), textureMap->tileHeight());
    _maxFrame = textureMap->width() / textureMap->tileWidth();
    _maxAnimation = textureMap->height() / textureMap->tileHeight();

    updateRectangle();
}

std::shared_ptr<twoCoords::TextureMap> twoCoords::SceneAnimatedObject::textureMap() const {
    return _textureMap.lock();
}

void twoCoords::SceneAnimatedObject::setFrame(int frame) {
    _frame = frame % _maxFrame;

    updateRectangle();
}

void twoCoords::SceneAnimatedObject::setFrame(int frame, int animation) {
    _frame = frame % _maxFrame;
    _animation = animation % _maxAnimation;

    updateRectangle();
}

void twoCoords::SceneAnimatedObject::setAnimation(int animation) {
    _animation = animation % _maxAnimation;

    updateRectangle();
}

int twoCoords::SceneAnimatedObject::frame() const {
    return _frame;
}

int twoCoords::SceneAnimatedObject::animation() const {
    return _animation;
}

void twoCoords::SceneAnimatedObject::updateRectangle() {
    auto textureMap = _textureMap.lock();
    if (textureMap == nullptr) {
        return;
    }

    // make and bind VAO and VBO
    if (_vao == 0) {
        glGenVertexArrays(1, &_vao);
    }

    glBindVertexArray(_vao);

    if (_vbo == 0) {
        glGenBuffers(1, &_vbo);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // set vertex data
    GLfloat texture = _animation * _maxFrame + _frame;

    GLfloat vertexData[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, texture,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, texture,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, texture,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, texture,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, texture,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, texture
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
