/**
 * Project: Two-Coords
 * File: src/textureMap.cpp
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

#include "textureMap.h"

#include "bitmap.h"

#include <spdlog/spdlog.h>

twoCoords::TextureMap::TextureMap(std::string filePath, GLfloat tileWidth, GLfloat tileHeight) : Texture(filePath) {
    _tileWidth = tileWidth;
    _tileHeight = tileHeight;
}

twoCoords::TextureMap::~TextureMap() {

}

bool twoCoords::TextureMap::load() {
    if (isLoaded()) {
        return true;
    }

    auto bitmap = Bitmap::bitmapFromFile(_filePath);
    if (bitmap == nullptr) {
        return false;
    }

    // get number of tiles
    int columns = bitmap->width() / roundf(_tileWidth);
    int rows = bitmap->height() / roundf(_tileHeight);
    int layers = columns * rows;

    // generate texture atlas from bitmap
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _object);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, bitmapFormatToTextureInternalFormat(bitmap->channels()), _tileWidth, _tileHeight, layers);

    // add layers
    const GLenum textureFormat = bitmapFormatToTextureFormat(bitmap->channels());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            auto tileBitmap = bitmap->rectFromBitmap(j * _tileWidth, i * _tileHeight, _tileWidth, _tileHeight);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i * columns + j, _tileWidth, _tileHeight, 1, textureFormat, GL_UNSIGNED_BYTE, tileBitmap->data());
        }
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    // save attributes
    _width = (GLfloat)bitmap->width();
    _height = (GLfloat)bitmap->height();
    _loaded = true;

    return true;
}

GLfloat twoCoords::TextureMap::tileWidth() const {
    return _tileWidth;
}

GLfloat twoCoords::TextureMap::tileHeight() const {
    return _tileHeight;
}
