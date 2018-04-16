/**
 * Project: Two-Coords
 * File: include/tileMap.h
 * Created: 09.04.2018
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

#include <cstdio>
#include <string>
#include <memory>

namespace twoCoords {
    class TileMap {
    private:
        int _width;
        int _height;
        int _layers;
        int ***_values;
        std::size_t _hash;

    public:
        TileMap(int width, int height, int layers = 1, int fillValue = -1);
        TileMap(const TileMap &other);
        virtual ~TileMap();

        int width() const;
        int height() const;
        int layers() const;
        std::size_t hash() const;

        void set(int x, int y, int layer, int value);
        int get(int x, int y, int layer) const;
        void clear(int x, int y, int layer);

        void fillLayer(int layer, int value);
        void fill(int value);
        void row(int row, int layer, int value);
        void column(int column, int layer, int value);
        void clearAll();
        void clearLayer(int layer);

        const TileMap &operator=(const TileMap &other);
        static std::shared_ptr<TileMap> tileMapFromFile(std::string filePath);

    private:
        void createValues();
        void copyValues(const TileMap &other);
        void deleteValues();

        void updateHash();
    };
}
