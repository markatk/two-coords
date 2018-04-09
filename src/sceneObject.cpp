/**
 * Project: Two-Coords
 * File: include/sceneObject.cpp
 * Created: 06.03.2018
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

#include "sceneObject.h"

#include "shaderProgram.h"
#include "texture.h"

GLuint twoCoords::SceneObject::_sVAO = 0;
GLuint twoCoords::SceneObject::_sVBO = 0;

twoCoords::SceneObject::SceneObject(std::shared_ptr<Texture> texture, glm::vec2 position) : SceneNode(position) {
    setTexture(texture);
}

twoCoords::SceneObject::~SceneObject() {

}

void twoCoords::SceneObject::render(std::shared_ptr<ShaderProgram> program) {
    auto texture = _texture.lock();
    if (texture == nullptr) {
        return;
    }

    program->setUniform("model", model());

    // load rectangle
    if (_sVAO == 0 || _sVBO == 0) {
        loadRectangle(program);
    }

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->object());
    program->setUniform("tex", 0);

    glBindVertexArray(_sVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

glm::vec2 twoCoords::SceneObject::size() const {
    return _size;
}

void twoCoords::SceneObject::setTexture(std::shared_ptr<Texture> texture) {
    _texture = texture;
    if (texture != nullptr) {
        _size = glm::vec2(texture->width(), texture->height());
    }
}

std::shared_ptr<twoCoords::Texture> twoCoords::SceneObject::texture() const {
    return _texture.lock();
}

bool twoCoords::SceneObject::inside(glm::vec2 point) const {
    auto position = worldPosition();
    return point.x >= position.x - _size.x * 0.5 && point.x < position.x + _size.x * 0.5 && point.y >= position.y - _size.y * 0.5 && point.y < position.y + _size.y * 0.5;
}

void twoCoords::SceneObject::loadRectangle(std::shared_ptr<ShaderProgram> program) const {
    // make and bind VAO and VBO
    glGenVertexArrays(1, &_sVAO);
    glBindVertexArray(_sVAO);

    glGenBuffers(1, &_sVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _sVBO);

    // add the rectangle
    GLfloat vertexData[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // connect attributes
    glEnableVertexAttribArray(program->attrib("vert"));
    glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(program->attrib("vertTexCoord"));
	glVertexAttribPointer(program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
