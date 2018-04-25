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

    glDrawArrays(GL_TRIANGLES, 0, 6 * _text.length());
}

void twoCoords::SceneText::setText(std::string text) {
    _text = text;

    auto font = _font.lock();
    if (font == nullptr) {
        return;
    }

    // calculate node size based on the text characters
    float width = 0;
    float height = 0;

    for (std::size_t i = 0; i < _text.length(); i++) {
        auto character = font->_characterCache[(int)_text[i]];

        // ax describes offset for next character (sligthly more than character.width)
        width += character.ax;
        height = std::max(height, character.height);
    }

    _size = glm::vec2(width, height);

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
    GLfloat offset = 0.f;

    glBufferData(GL_ARRAY_BUFFER, 30 * _text.length() * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

    for (std::size_t i = 0; i < _text.length(); i++) {
        auto character = font->_characterCache[(int)_text[i]];

        auto textureOffset = character.offset / font->_textureWidth;
        auto textureWidth = character.width / font->_textureWidth;
        auto textureHeight = character.height / font->_textureHeight;

        auto positionWidth = character.width / _size.x;
        auto verticalOffset = 1.f - character.height / _size.y;

        GLfloat charVertexData[30] = {
            -0.5f + offset, -0.5f + verticalOffset, 0.f, textureOffset, 0.f,
            -0.5f + offset, 0.5f, 0.f, textureOffset, textureHeight,
            -0.5f + offset + positionWidth, -0.5f + verticalOffset, 0.f, textureOffset + textureWidth, 0.f,
            -0.5f + offset + positionWidth, -0.5f + verticalOffset, 0.f, textureOffset + textureWidth, 0.f,
            -0.5f + offset + positionWidth, 0.5f, 0.f, textureOffset + textureWidth, textureHeight,
            -0.5f + offset, 0.5f, 0.f, textureOffset, textureHeight
        };

        glBufferSubData(GL_ARRAY_BUFFER, i * 30 * sizeof(GLfloat), 30 * sizeof(GLfloat), charVertexData);

        offset += character.ax / _size.x;
    }

    // unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
