/**
 * Project: Two-Coords
 * File: src/shader.cpp
 * Created: 13.02.2018
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

#include "shader.h"

#include <sstream>
#include <cassert>

twoCoords::Shader::Shader(const std::string &code, GLenum type) {
    // create shader object
    _object = glCreateShader(type);
    if (_object == 0) {
        throw std::runtime_error("glCreateShader failed");
    }

    // set source code
    const char *shaderCode = code.c_str();
    glShaderSource(_object, 1, (const GLchar **)&shaderCode, NULL);

    // compile shader
    glCompileShader(_object);

    // check if everything is play
    GLint status;
    glGetShaderiv(_object, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        // generate error message
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(_object, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        // delete shader
        glDeleteShader(_object);
        _object = 0;

        throw std::runtime_error(msg);
    }

    // create reference counter
    _referenceCount = std::make_shared<unsigned>();
    *_referenceCount = 1;
}

twoCoords::Shader::Shader(const Shader &other) {
    _object = other._object;
    _referenceCount = other._referenceCount;

    retain();
}

twoCoords::Shader::~Shader() {
    if (_referenceCount) {
        release();
    }
}

GLuint twoCoords::Shader::object() const {
    return _object;
}

twoCoords::Shader &twoCoords::Shader::operator=(const Shader &other) {
    // release old object
    release();

    _object = other._object;
    _referenceCount = other._referenceCount;

    // retain new object
    retain();

    return *this;
}

void twoCoords::Shader::retain() {
    assert(_referenceCount);
    *_referenceCount += 1;
}

void twoCoords::Shader::release() {
    assert(_referenceCount && *_referenceCount > 0);
    *_referenceCount -= 1;

    // check if the object should be destroyed
    if (*_referenceCount <= 0) {
        glDeleteShader(_object);
        _object = 0;

        _referenceCount = nullptr;
    }
}
