/**
 * Project: Two-Coords
 * File: src/sceneText.cpp
 * Created: 17.04.2018
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

#include "sceneText.h"

#include "font.h"
#include "shaderProgram.h"

#include <spdlog/spdlog.h>
#include <string>

twoCoords::SceneText::SceneText(std::shared_ptr<Font> font, std::string text, glm::vec2 position) : SceneNode(position) {
    _font = font;
    
    setText(text);
}

twoCoords::SceneText::~SceneText() {

}

void twoCoords::SceneText::render(std::shared_ptr<ShaderProgram> program) {
    auto font = _font.lock();
    if (font == nullptr) {
        return;
    }

    program->setUniform("model", model());

    // connect attributes
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(program->attrib("vert"));
    glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(program->attrib("vertTexCoord"));
	glVertexAttribPointer(program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->texture());
    program->setUniform("tex", 0);

    // glDrawArrays(GL_TRIANGLES, 0, 6 * _text.length());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void twoCoords::SceneText::setText(std::string text) {
    _text = text;

    auto font = _font.lock();
    if (font == nullptr) {
        return;
    }

    float width = 0;
    float height = 0;

    for (std::size_t i = 0; i < _text.length(); i++) {
        auto character = font->_characterCache[(int)_text[i]];

        width += character.width;
        height = std::max(height, character.height);
    }

    _size = glm::vec2(width * font->_textureWidth, height * font->_textureHeight);
    // _size = glm::vec2(600, 40);

    updateVertexArray(font);
}

std::string twoCoords::SceneText::text() const {
    return _text;
}

void twoCoords::SceneText::updateVertexArray(std::shared_ptr<Font> font) {
    // make and bind VAO and VBO
    if (_vao == 0) {
        glGenVertexArrays(1, &_vao);
    }

    glBindVertexArray(_vao);

    if (_vbo == 0) {
        glGenBuffers(1, &_vbo);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // add character rectangles
    GLfloat stepX = 1.f / _text.length();

    GLfloat *vertexData = new GLfloat[30 * _text.length()];
    memset(vertexData, 0, 30 * _text.length() * sizeof(GLfloat));

    for (std::size_t i = 0; i < _text.length(); i++) {
        auto character = font->_characterCache[(int)_text[i]];

        GLfloat charVertexData[30] = {
            -0.5f + stepX * i, -0.5f, 0.f, character.offset, 0.f,
            -0.5f + stepX * i, 0.5f, 0.f, character.offset, character.height,
            -0.5f + stepX * (i + 1), -0.5f, 0.f, character.offset + character.width, 0.f,
            -0.5f + stepX * (i + 1), -0.5f, 0.f, character.offset + character.width, 0.f,
            -0.5f + stepX * (i + 1), 0.5f, 0.f, character.offset + character.width, character.height,
            -0.5f + stepX * i, 0.5f, 0.f, character.offset, character.height
        };

        memcpy(&vertexData[i * 30], charVertexData, 30 * sizeof(GLfloat));
    }

    glBufferData(GL_ARRAY_BUFFER, 30 * _text.length() * sizeof(GLfloat), vertexData, GL_DYNAMIC_DRAW);

    delete [] vertexData;

    // GLfloat vertexData[] = {
	// 	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	// 	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	// 	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	// 	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	// 	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	// 	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    // };

    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
