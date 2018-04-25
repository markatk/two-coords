/**
 * Project: Two-Coords
 * File: src/font.cpp
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

#include "font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <spdlog/spdlog.h>
#include <algorithm>

#include "twoCoords.h"

#include <iostream>

twoCoords::Font::Font(std::string filePath, int size) : Resource(filePath) {
    _size = size;
    _textureWidth = 0;
    _textureHeight = 0;
}

twoCoords::Font::~Font() {

}

bool twoCoords::Font::load() {
    // load font file
    FT_Face fontFace;
    if (FT_New_Face(twoCoords::freetypeHandle(), _filePath.c_str(), 0, &fontFace) != 0) {
        spdlog::get("console")->warn("Unable to load font file: " + _filePath);
        return false;
    }

    FT_Set_Pixel_Sizes(fontFace, 0, _size);

    // calculate texture size
    int totalWidth = 0;
    int maxHeight = 0;

    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER) != 0) {
            spdlog::get("console")->warn("Unable to load character " + std::to_string(i) + " of font: " + _filePath);
            continue;
        }

        totalWidth += fontFace->glyph->bitmap.width;
        maxHeight = std::max(maxHeight, (int)fontFace->glyph->bitmap.rows);
    }

    // create atlas texture
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, totalWidth, maxHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    // generate font texture
    int offset = 0;

    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER) != 0) {
            spdlog::get("console")->warn("Unable to load texture for character " + std::to_string(i) + " of font: " + _filePath);
            continue;
        }

        // store character info
        auto glyph = fontFace->glyph;

        _characterCache[i].ax = glyph->advance.x >> 6;
        _characterCache[i].ay = glyph->advance.y >> 6;
        _characterCache[i].width = glyph->bitmap.width;
        _characterCache[i].height = glyph->bitmap.rows;
        _characterCache[i].left = glyph->bitmap_left;
        _characterCache[i].top = glyph->bitmap_top;
        _characterCache[i].offset = offset;

        glTexSubImage2D(GL_TEXTURE_2D, 0, offset, 0, glyph->bitmap.width, glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

        offset += glyph->bitmap.width;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    _textureWidth = totalWidth;
    _textureHeight = maxHeight;

    return true;
}

void twoCoords::Font::setSize(int size) {
    _size = size;
}

int twoCoords::Font::size() const {
    return _size;
}

GLuint twoCoords::Font::texture() const {
    return _object;
}
