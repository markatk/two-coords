/**
 * Project: Two-Coords
 * File: src/tileMap.cpp
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

#include "tileMap.h"

twoCoords::TileMap::TileMap(int width, int height, int fillValue) {
    _width = width;
    _height = height;

    createValues();
    fill(fillValue);
}

twoCoords::TileMap::TileMap(const TileMap &other) {
    _width = other._width;
    _height = other._height;

    createValues();
    copyValues(other);
}

twoCoords::TileMap::~TileMap() {
    deleteValues();
}

int twoCoords::TileMap::width() const {
    return _width;
}

int twoCoords::TileMap::height() const {
    return _height;
}

void twoCoords::TileMap::set(int x, int y, int value) {
    _values[x][y] = value;
}

int twoCoords::TileMap::get(int x, int y) const {
    return _values[x][y];
}

void twoCoords::TileMap::fill(int value) {
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            _values[i][j] = value;
        }
    }
}

const twoCoords::TileMap &twoCoords::TileMap::operator=(const TileMap &other) {
    _width = other._width;
    _height = other._height;

    deleteValues();
    createValues();
    copyValues(other);
}

void twoCoords::TileMap::createValues() {
    _values = new int*[_width];

    for (int i = 0; i < _width; i++) {
        _values[i] = new int[_height];
    }
}

void twoCoords::TileMap::copyValues(const TileMap &other) {
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            _values[i][j] = other.get(i, j);
        }
    }
}

void twoCoords::TileMap::deleteValues() {
    for (int i = 0; i < _width; i++) {
        delete [] _values[i];
    }

    delete [] _values;
}
