/**
 * Project: Two-Coords
 * File: include/soundBuffer.cpp
 * Created: 23.03.2018
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

#include "soundBuffer.h"

#include <spdlog/spdlog.h>
#include <AL/alut.h>

twoCoords::SoundBuffer::SoundBuffer(std::string filePath) : twoCoords::Resource(filePath), _buffer(0) {

}

twoCoords::SoundBuffer::~SoundBuffer() {
    if (_buffer != 0) {
        alDeleteBuffers(1, &_buffer);
    }
}

bool twoCoords::SoundBuffer::load() {
    if (isLoaded()) {
        return true;
    }

    _buffer = alutCreateBufferFromFile(_filePath.c_str());
    auto error = alutGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        spdlog::get("console")->error("Unable to load sound file " + _filePath + ": (" + std::to_string(error) + ") " + alutGetErrorString(error));
        return false;
    }

    _loaded = true;
    return true;
}

ALuint twoCoords::SoundBuffer::buffer() const {
    return _buffer;
}
