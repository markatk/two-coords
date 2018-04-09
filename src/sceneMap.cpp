/**
 * Project: Two-Coords
 * File: src/sceneMap.cpp
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

#include "sceneMap.h"

#include "shaderProgram.h"
#include "textureMap.h"

#include <spdlog/spdlog.h>

twoCoords::SceneMap::SceneMap(std::shared_ptr<TextureMap> textureMap, glm::vec2 tiles, glm::vec2 position) : SceneObject(nullptr, position) {
    _tiles = tiles;
    _size = glm::vec2(0);

    setTextureMap(textureMap);
}

twoCoords::SceneMap::~SceneMap() {

}

void twoCoords::SceneMap::render(std::shared_ptr<ShaderProgram> program) {
    auto textureMap = _textureMap.lock();
    if (textureMap == nullptr) {
        return;
    }

    // load rectangle
    if (_sVAO == 0 || _sVBO == 0) {
        loadRectangle(program);
    }

    // draw tiles
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureMap->object());
    program->setUniform("tex", 0);
    program->setUniform("layer", 0);

    glBindVertexArray(_sVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void twoCoords::SceneMap::setTiles(glm::vec2 tiles) {
    _tiles = tiles;
    
    if (auto textureMap = _textureMap.lock()) {
        _size = _tiles * glm::vec2(textureMap->tileWidth(), textureMap->tileHeight());
    } else {
        _size = glm::vec2(0);
    }
}

glm::vec2 twoCoords::SceneMap::tiles() const {
    return _tiles;
}

void twoCoords::SceneMap::setTextureMap(std::shared_ptr<TextureMap> textureMap) {
    _textureMap = textureMap;

    setTiles(_tiles);
}

std::shared_ptr<twoCoords::TextureMap> twoCoords::SceneMap::textureMap() const {
    return _textureMap.lock();
}

bool twoCoords::SceneMap::inside(glm::vec2 point) const {
    return SceneObject::inside(point);
}
