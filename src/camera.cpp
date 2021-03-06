/**
 * Project: Two-Coords
 * File: include/camera.cpp
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

#include "camera.h"

#ifdef __APPLE__
#include <OpenAL/al.h>
#else
#include <AL/al.h>
#endif

twoCoords::Camera::Camera() {
    _position = glm::vec2(0);
    _rotation = 0.f;
    _zoom = 1.f;
}

twoCoords::Camera::~Camera() {

}

void twoCoords::Camera::setPosition(glm::vec2 position) {
    _position = position;

    alListener3f(AL_POSITION, position.x, position.y, 0);
}

glm::vec2 twoCoords::Camera::position() const {
    return _position;
}

void twoCoords::Camera::setZoom(float zoom) {
    _zoom = zoom;
}

float twoCoords::Camera::zoom() const {
    return _zoom;
}

void twoCoords::Camera::setRotation(float rotation) {
    _rotation = rotation;
}

float twoCoords::Camera::rotation() const {
    return _rotation;
}
