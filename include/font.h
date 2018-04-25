/**
 * Project: Two-Coords
 * File: include/font.h
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

#pragma once

#include "resource.h"

#include <string>
#include <GL/glew.h>

namespace twoCoords {
    class SceneText;

    class Font : public Resource {
    private:
        struct {
            float ax;
            float ay;

            float width;
            float height;

            float left;
            float top;

            float offset;
        } _characterCache[128];

        int _size;
        GLfloat _textureWidth;
        GLfloat _textureHeight;

        GLuint _object;

    public:
        Font(std::string filePath, int size);
        virtual ~Font();

        bool load();

        void setSize(int size);
        int size() const;

        GLuint texture() const;

    private:
        bool initializeLibrary();

        // disable copying
        Font(const Font &);
        const Font &operator=(const Font &);

        friend SceneText;
    };
}
