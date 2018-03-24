/**
 * Project: Two-Coords
 * File: include/sceneObject.h
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

#pragma once

#include "sceneNode.h"

#include <GL/glew.h>
#include <memory>

namespace twoCoords {
    class Texture;

    class SceneObject : public SceneNode {
    private:
        std::weak_ptr<Texture> _texture;

        static GLuint _sVAO;
        static GLuint _sVBO;

    public:
        SceneObject(std::shared_ptr<Texture> texture, glm::vec2 position = glm::vec2(0));
        virtual ~SceneObject();

        virtual void render(std::shared_ptr<ShaderProgram> program);

        glm::vec2 size() const;

        void setTexture(std::shared_ptr<Texture> texture);
        std::shared_ptr<Texture> texture() const;

        bool inside(glm::vec2 point) const;

    private:
        void loadRectangle(std::shared_ptr<ShaderProgram> program) const;
    };
}
