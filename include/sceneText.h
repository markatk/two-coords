/**
 * Project: Two-Coords
 * File: include/sceneText.h
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

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>

#include "sceneNode.h"

namespace twoCoords {
    class Font;
    class ShaderProgram;

    class SceneText : public SceneNode {
    private:
        std::weak_ptr<Font> _font;
        std::string _text;

        GLuint _vao;
        GLuint _vbo;

    public:
        SceneText(std::shared_ptr<Font> font, std::string text, glm::vec2 position = glm::vec2(0));
        virtual ~SceneText();

        virtual void render(std::shared_ptr<ShaderProgram> program);

        void setText(std::string text);
        std::string text() const;

    private:
        void updateVertexArray(std::shared_ptr<Font> font);
    };
}
