/**
 * Project: Two-Coords
 * File: include/bitmap.cpp
 * Created: 05.03.2018
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

#include "bitmap.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

twoCoords::Bitmap::Bitmap(unsigned int width, unsigned int height, unsigned int channels, unsigned char *data) {
    _data = nullptr;
    _filePath = "";

    setData(width, height, channels, data);
}

twoCoords::Bitmap::~Bitmap() {
    if (_data != nullptr) {
        free(_data);
    }
}

unsigned int twoCoords::Bitmap::width() const {
    return _width;
}

unsigned int twoCoords::Bitmap::height() const {
    return _height;
}

unsigned int twoCoords::Bitmap::channels() const {
    return _channels;
}

unsigned char *twoCoords::Bitmap::data() const {
    return _data;
}

std::string twoCoords::Bitmap::filePath() const {
    return _filePath;
}

bool twoCoords::Bitmap::setData(unsigned int width, unsigned int height, unsigned int channels, unsigned char *data) {
    if (width == 0 || height == 0 || channels == 0 || channels > 4 || data == nullptr) {
        return false;
    }

    _width = width;
    _height = height;
    _channels = channels;

    // allocate memory for bitmap
    size_t size = width * height * channels;
    if (_data != nullptr) {
        _data = (unsigned char *)realloc(_data, size * sizeof(unsigned char));
    } else {
        _data = (unsigned char *)malloc(size * sizeof(unsigned char));
    }

    memcpy(_data, data, size);
    return true;
}

std::shared_ptr<twoCoords::Bitmap> twoCoords::Bitmap::rectFromBitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const {
    if (x >= _width || y >= _height || width == 0 || height == 0 || x + width > _width || y + height > _height) {
        return nullptr;
    }

    // copy rect into buffer
    unsigned char *rectData = (unsigned char *)malloc(width * height * _channels);
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < width; j++) {
            memcpy(rectData + (i * width + j) * _channels, _data + pixelOffset(x + i, y + i), _channels);
        }
    }

    // generate bitmap from buffer
    auto bitmap = std::make_shared<Bitmap>(width, height, _channels, rectData);
    free(rectData);

    return bitmap;
}

std::shared_ptr<twoCoords::Bitmap> twoCoords::Bitmap::bitmapFromFile(std::string filePath) {
    int width, height, channels;
    auto data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data == NULL) {
        return nullptr;
    }

    // create bitmap
    auto bitmap = std::make_shared<Bitmap>(width, height, channels, data);
    bitmap->_filePath = filePath;

    stbi_image_free(data);
    return bitmap;
}

unsigned int twoCoords::Bitmap::pixelOffset(unsigned int x, unsigned int y) const {
    return (y * _width + x) * _channels;
}
