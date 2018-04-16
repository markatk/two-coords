/**
 * Project: Two-Coords
 * File: include/sceneAnimatedObject.h
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

#pragma once

#include "sceneObject.h"

namespace twoCoords {
    class TextureMap;

    class SceneAnimatedObject : public SceneObject {
    protected:
        std::weak_ptr<TextureMap> _textureMap;
        int _frame;
        int _animation;
        
        int _maxFrame;
        int _maxAnimation;

        GLuint _vao;
        GLuint _vbo;

    public:
        SceneAnimatedObject(std::shared_ptr<TextureMap> textureMap, glm::vec2 position = glm::vec2(0));
        virtual ~SceneAnimatedObject();

        virtual void render(std::shared_ptr<ShaderProgram> program);

        void setTextureMap(std::shared_ptr<TextureMap> textureMap);
        std::shared_ptr<TextureMap> textureMap() const;

        void setFrame(int frame);
        void setFrame(int frame, int animation);
        void setAnimation(int animation);
        int frame() const;
        int animation() const;

    private:
        void updateRectangle();
    };
}
