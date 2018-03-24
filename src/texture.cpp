/**
 * Project: Two-Coords
 * File: include/texture.cpp
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

#include "texture.h"

#include "bitmap.h"

#include <spdlog/spdlog.h>

twoCoords::Texture::Texture(std::string filePath) : Resource(filePath) {
    _object = 0;
    _width = 0;
    _height = 0;
}

twoCoords::Texture::~Texture() {
    if (_object != 0) {
        glDeleteTextures(1, &_object);
    }
}

bool twoCoords::Texture::load() {
    if (isLoaded()) {
        return true;
    }

    auto bitmap = Bitmap::bitmapFromFile(_filePath);
    if (bitmap == nullptr) {
        return false;
    }

    // generate texture from bitmap
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

    // set texture
    const GLenum textureFormat = bitmapFormatToTextureFormat(bitmap->channels());
    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, bitmap->width(), bitmap->height(), 0, textureFormat, GL_UNSIGNED_BYTE, bitmap->data());

    glBindTexture(GL_TEXTURE_2D, 0);

    // save attributes
    _width = (GLfloat)bitmap->width();
    _height = (GLfloat)bitmap->height();
    _loaded = true;

    return true;
}

GLuint twoCoords::Texture::object() const {
    return _object;
}

GLfloat twoCoords::Texture::width() const {
    return _width;
}

GLfloat twoCoords::Texture::height() const {
    return _height;
}

GLenum twoCoords::Texture::bitmapFormatToTextureFormat(unsigned int channels) {
    switch (channels) {
        case 1:
            return GL_LUMINANCE;

        case 2:
            return GL_LUMINANCE_ALPHA;

        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;

        default:
            throw std::string("Not supported number of bitmap channels") + std::to_string(channels);
    }
}
