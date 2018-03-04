/**
 * Project: Two-Coords
 * File: include/bitmap.h
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

#pragma once

#include <string>
#include <memory>

namespace twoCoords {
  class Bitmap {
  private:
    unsigned int _width;
    unsigned int _height;
    unsigned int _channels;
    unsigned char *_data;

    std::string _filePath;

  public:
    Bitmap(unsigned int width, unsigned int height, unsigned int channels, unsigned char *data);
    virtual ~Bitmap();

    unsigned int width() const;
    unsigned int height() const;
    unsigned int channels() const;
    unsigned char *data() const;

    std::string filePath() const;

    bool setData(unsigned int width, unsigned int height, unsigned int channels, unsigned char *data);
    std::shared_ptr<Bitmap> rectFromBitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
    static std::shared_ptr<Bitmap> bitmapFromFile(std::string filePath);

  private:
    unsigned int pixelOffset(unsigned int x, unsigned int y) const;
  };
}
