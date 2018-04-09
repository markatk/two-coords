/**
 * Project: Two-Coords
 * File: include/sceneMap.h
 * Created: 08.04.2018
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

    class SceneMap : public SceneObject {
    protected:
        std::weak_ptr<TextureMap> _textureMap;
        glm::vec2 _tiles;

    public:
        SceneMap(std::shared_ptr<TextureMap> textureMap, glm::vec2 tiles, glm::vec2 position = glm::vec2(0));
        virtual ~SceneMap();

        virtual void render(std::shared_ptr<ShaderProgram> program);

        void setTiles(glm::vec2 tiles);
        glm::vec2 tiles() const;

        void setTextureMap(std::shared_ptr<TextureMap> textureMap);
        std::shared_ptr<TextureMap> textureMap() const;

        bool inside(glm::vec2 point) const;
    };
}
