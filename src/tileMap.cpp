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

#include <functional>
#include <vector>
#include <sstream>
#include <fstream>

#include <spdlog/spdlog.h>

twoCoords::TileMap::TileMap(int width, int height, int layers, int fillValue) {
    _width = width;
    _height = height;
    _layers = layers;

    createValues();
    fill(fillValue);
}

twoCoords::TileMap::TileMap(const TileMap &other) {
    _width = other._width;
    _height = other._height;
    _layers = other._layers;

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

int twoCoords::TileMap::layers() const {
    return _layers;
}

std::size_t twoCoords::TileMap::hash() const {
    return _hash;
}

void twoCoords::TileMap::set(int x, int y, int layer, int value) {
    if (x < 0 || x >= _width) {
        throw new std::runtime_error("X value is not valid for tilemap");
    }

    if (y < 0 || y >= _height) {
        throw new std::runtime_error("Y value is not valid for tilemap");
    }

    if (layer < 0 || layer >= _layers) {
        throw new std::runtime_error("Layer value is not valid for tilemap");
    }

    _values[layer][x][y] = value;

    updateHash();
}

int twoCoords::TileMap::get(int x, int y, int layer) const {
    if (x < 0 || x >= _width) {
        throw new std::runtime_error("X value is not valid for tilemap");
    }

    if (y < 0 || y >= _height) {
        throw new std::runtime_error("Y value is not valid for tilemap");
    }

    if (layer < 0 || layer >= _layers) {
        throw new std::runtime_error("Layer value is not valid for tilemap");
    }

    return _values[layer][x][y];
}

void twoCoords::TileMap::clear(int x, int y, int layer) {
    set(x, y, layer, -1);
}

void twoCoords::TileMap::fillLayer(int layer, int value) {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _values[layer][i][j] = value;
        }
    }

    updateHash();
}

void twoCoords::TileMap::fill(int value) {
    for (int i = 0; i < _layers; i++) {
        for (int j = 0; j < _width; j++) {
            for (int k = 0; k < _height; k++) {
                _values[i][j][k] = value;
            }
        }
    }

    updateHash();
}

void twoCoords::TileMap::row(int row, int layer, int value) {
    if (row < 0 || row >= _height) {
        throw new std::runtime_error("Row is not valid for tilemap");
    }

    if (layer < 0 || layer >= _layers) {
        throw new std::runtime_error("Layer value is not valid for tilemap");
    }

    for (int x = 0; x < _width; x++) {
        _values[layer][x][row] = value;
    }

    updateHash();
}

void twoCoords::TileMap::column(int column, int layer, int value) {
    if (column < 0 || column >= _width) {
        throw new std::runtime_error("Column is not valid for tilemap");
    }

    if (layer < 0 || layer >= _layers) {
        throw new std::runtime_error("Layer value is not valid for tilemap");
    }

    for (int y = 0; y < _height; y++) {
        _values[layer][column][y] = value;
    }

    updateHash();
}

void twoCoords::TileMap::clearAll() {
    fill(-1);
}

void twoCoords::TileMap::clearLayer(int layer) {
    fillLayer(layer, -1);
}

bool twoCoords::TileMap::layerFromFile(int layer, std::string filePath) {
    // read csv file
    std::vector<std::vector<int>> data;
    std::ifstream file(filePath);

    while (file) {
        std::string line;
        if (!std::getline(file, line)) {
            break;
        }

        if (line[0] == '#') {
            continue;
        }

        std::istringstream lineStream(line);
        std::vector<int> lineData;

        while (lineStream) {
            std::string value;
            if (!std::getline(lineStream, value, ',')) {
                break;
            }

            try {
                lineData.push_back(std::stoi(value));
            } catch (std::exception e) {
                spdlog::get("console")->warn("Unable to parse tilemap value: " + std::string(e.what()));
            }
        }

        data.push_back(lineData);
    }

    if (file.eof() == false) {
        spdlog::get("console")->warn("Unable to read tilemap file: " + filePath);
        return false;
    }

    // create map
    std::size_t height = 0;

    for (auto it = data.begin(); it != data.end(); it++) {
        if ((*it).size() > height) {
            height = (*it).size();
        }
    }

    auto tileMap = std::make_shared<TileMap>(data.size(), height);

    for (std::size_t y = 0; y < data.size(); y++) {
        for (std::size_t x = 0; x < data[y].size(); x++) {
            _values[layer][x][y] = data[y][x];
        }
    }

    return true;
}

const twoCoords::TileMap &twoCoords::TileMap::operator=(const TileMap &other) {
    _width = other._width;
    _height = other._height;

    deleteValues();
    createValues();
    copyValues(other);

    return *this;
}

std::shared_ptr<twoCoords::TileMap> twoCoords::TileMap::tileMapFromFile(std::string filePath, int width, int height) {
    auto tileMap = std::make_shared<TileMap>(width, height);
    if (tileMap->layerFromFile(0, filePath) == false) {
        return nullptr;
    }

    return tileMap;
}

void twoCoords::TileMap::createValues() {
    _values = new int**[_layers];

    for (int i = 0; i < _layers; i++) {
        _values[i] = new int*[_width];

        for (int j = 0; j < _width; j++) {
            _values[i][j] = new int[_height];
        }
    }
}

void twoCoords::TileMap::copyValues(const TileMap &other) {
    if (_width != other._width) {
        throw new std::runtime_error("Width does not match other's width");
    }

    if (_height != other._height) {
        throw new std::runtime_error("Height does not match other's height");
    }

    if (_layers != other._layers) {
        throw new std::runtime_error("Layers count does not match other's layers count");
    }

    for (int i = 0; i < _layers; i++) {
        for (int j = 0; j < _height; j++) {
            for (int k = 0; k < _width; k++) {
                _values[i][j][k] = other.get(j, k, i);
            }
        }
    }

    updateHash();
}

void twoCoords::TileMap::deleteValues() {
    for (int i = 0; i < _layers; i++) {
        for (int j = 0; j < _width; j++) {
            delete [] _values[i][j];
        }

        delete [] _values[i];
    }

    delete [] _values;
}

void twoCoords::TileMap::updateHash() {
    _hash = 0;

    std::hash<int> hasher;

    for (int i = 0; i < _layers; i++) {
        for (int j = 0; j < _width; j++) {
            for (int k = 0; k < _height; k++) {
                _hash ^= hasher(_values[i][j][k]) + 0x9a377bc2 + (_hash << 6) + (_hash >> 2);
            }
        }
    }
}
