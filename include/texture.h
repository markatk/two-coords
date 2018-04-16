/**
 * Project: Two-Coords
 * File: include/texture.h
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

#include "resource.h"

#include <GL/glew.h>

namespace twoCoords {
    class Bitmap;

    class Texture : public Resource {
    protected:
        GLuint _object;
        GLfloat _width;
        GLfloat _height;

    public:
        Texture(std::string filePath);
        virtual ~Texture();

        bool load() override;

        GLuint object() const;
        GLfloat width() const;
        GLfloat height() const;

    protected:
        static GLenum bitmapFormatToTextureFormat(unsigned int channels);
        static GLenum bitmapFormatToTextureInternalFormat(unsigned int channels);

    private:
        // disable copying
        Texture(const Texture &);
        const Texture &operator=(const Texture &);
    };
}