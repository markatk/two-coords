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
#include "tileMap.h"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

twoCoords::SceneMap::SceneMap(std::shared_ptr<TextureMap> textureMap, std::shared_ptr<TileMap> tileMap, glm::vec2 position) : SceneObject(nullptr, position) {
    _size = glm::vec2(0);
    _tileMapHash = 0;
    _vao = 0;
    _vbo = 0;

    setTileMap(tileMap);
    setTextureMap(textureMap);
}

twoCoords::SceneMap::~SceneMap() {

}

void twoCoords::SceneMap::render(std::shared_ptr<ShaderProgram> program) {
    auto textureMap = _textureMap.lock();
    if (textureMap == nullptr) {
        return;
    }

    if (_tileMapHash != _tileMap->hash()) {
        _tileMapHash = _tileMap->hash();

        updateRectangleMap();
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

    glDrawArrays(GL_TRIANGLES, 0, 6 * _tileMap->width() * _tileMap->height());
}

void twoCoords::SceneMap::setTileMap(std::shared_ptr<TileMap> tileMap) {
    _tileMap = tileMap;
    
    calculateSize();
}

std::shared_ptr<twoCoords::TileMap> twoCoords::SceneMap::tileMap() const {
    return _tileMap;
}

void twoCoords::SceneMap::setTextureMap(std::shared_ptr<TextureMap> textureMap) {
    _textureMap = textureMap;

    calculateSize();
}

std::shared_ptr<twoCoords::TextureMap> twoCoords::SceneMap::textureMap() const {
    return _textureMap.lock();
}

bool twoCoords::SceneMap::inside(glm::vec2 point) const {
    return SceneObject::inside(point);
}

void twoCoords::SceneMap::calculateSize() {
    if (_tileMap == nullptr) {
        _size = glm::vec2(0);
        return;
    }

    if (auto textureMap = _textureMap.lock()) {
        _size = glm::vec2(_tileMap->width() * textureMap->tileWidth(), _tileMap->height() * textureMap->tileHeight());
    } else {
        _size = glm::vec2(0);
    }
}

void twoCoords::SceneMap::updateRectangleMap() {
    // make and bind VAO and VBO
    if (_vao == 0) {
        glGenVertexArrays(1, &_vao);
    }

    glBindVertexArray(_vao);

    if (_vbo == 0) {
        glGenBuffers(1, &_vbo);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // add rectangles
    const int TILE_SIZE = 6 * 6;
    int tiles = _tileMap->width() * _tileMap->height();
    GLfloat stepX = 1.f/ _tileMap->width();
    GLfloat stepY = 1.f/ _tileMap->height();

    // render each layer
    GLfloat *vertexData = new GLfloat[TILE_SIZE * tiles];

    for (int i = 0; i < _tileMap->layers(); i++) {
        memset(vertexData, 0, TILE_SIZE * tiles * sizeof(GLfloat));

        for (int y = 0; y < _tileMap->width(); y++) {
            for (int x = 0; x < _tileMap->height(); x++) {
                if (_tileMap->get(x, y, i) == -1) {
                    continue;
                }

                GLfloat tileVertexData[TILE_SIZE] = {
                    -0.5f + stepX * x, -0.5f + stepY * y, 0.f, 0.f, 0.f, (GLfloat)_tileMap->get(x, y, i),
                    -0.5f + stepX * x, -0.5f + stepY * (y + 1), 0.f, 0.f, 1.f, (GLfloat)_tileMap->get(x, y, i),
                    -0.5f + stepX * (x + 1), -0.5f + stepY * y, 0.f, 1.f, 0.f, (GLfloat)_tileMap->get(x, y, i),
                    -0.5f + stepX * (x + 1), -0.5f + stepY * y, 0.f, 1.f, 0.f, (GLfloat)_tileMap->get(x, y, i),
                    -0.5f + stepX * (x + 1), -0.5f + stepY * (y + 1), 0.f, 1.f, 1.f, (GLfloat)_tileMap->get(x, y, i),
                    -0.5f + stepX * x, -0.5f + stepY * (y + 1), 0.f, 0.f, 1.f, (GLfloat)_tileMap->get(x, y, i)
                };

                memcpy(&vertexData[(y * _tileMap->width() + x) * TILE_SIZE], tileVertexData, TILE_SIZE * sizeof(GLfloat));
            }
        }

        glBufferData(GL_ARRAY_BUFFER, TILE_SIZE * tiles * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
    }

    delete [] vertexData;

    // unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
