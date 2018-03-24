/**
 * Project: Two-Coords
 * File: src/shaderProgram.cpp
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

#include "shaderProgram.h"

#include "shader.h"

#include <string>
#include <glm/gtc/type_ptr.hpp>

twoCoords::ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders) {
    if (shaders.size() < 1) {
        throw std::runtime_error("No shaders were provided to create the shader program");
    }

    // create program
    _object = glCreateProgram();
    if (_object == 0) {
        throw std::runtime_error("glCreateProgram failed");
    }

    // attach all shaders
    for (unsigned int i = 0; i < shaders.size(); i++) {
        glAttachShader(_object, shaders[i].object());
    }

    glLinkProgram(_object);

    // detach all shaders after linking
    for (unsigned int i = 0; i < shaders.size(); i++) {
        glDetachShader(_object, shaders[i].object());
    }

    // check if linking succeeded
    GLint status;
    glGetProgramiv(_object, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        // generate error message
        std::string msg("Program linking failure:\n");

        GLint infoLogLength;
		glGetProgramiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
		char *strInfoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(_object, infoLogLength, NULL, strInfoLog);
		msg += strInfoLog;
		delete[] strInfoLog;

		// delete program
		glDeleteProgram(_object);
		_object = 0;

		throw std::runtime_error(msg);
    }
}

twoCoords::ShaderProgram::~ShaderProgram() {
    if (_object != 0) {
        glDeleteProgram(_object);
    }
}

void twoCoords::ShaderProgram::use() const {
    glUseProgram(_object);
}

void twoCoords::ShaderProgram::stopUsing() const {
    if (isInUse()) {
        glUseProgram(0);
    }
}

bool twoCoords::ShaderProgram::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == (GLint)_object);
}

GLint twoCoords::ShaderProgram::attrib(const GLchar *name) const {
    if (name == NULL) {
        throw std::runtime_error("Attribute name is NULL");
    }

    // get attribute
    GLint attrib = glGetAttribLocation(_object, name);
    if (attrib == -1) {
        throw std::runtime_error(std::string("Program attribute not found: ") + name);
    }

    return attrib;
}

GLint twoCoords::ShaderProgram::uniform(const GLchar *name) const {
    if (name == NULL) {
        throw std::runtime_error("Uniform name is NULL");
    }

    GLint uniform = glGetUniformLocation(_object, name);
    if (uniform == -1) {
        throw std::runtime_error(std::string("Program uniform not found: ") + name);
    }

    return uniform;
}

void twoCoords::ShaderProgram::setUniform(const GLchar *name, const glm::mat4 &matrix, GLboolean transpose) {
    if (isInUse() == false) {
        throw std::runtime_error("Program is not in use while setting uniform");
    }

    glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(matrix));
}

void twoCoords::ShaderProgram::setUniform(const GLchar *name, const GLuint value) {
    if (isInUse() == false) {
        throw std::runtime_error("Program is not in use while setting uniform");
    }

    glUniform1i(uniform(name), value);
}

GLuint twoCoords::ShaderProgram::object() const {
    return _object;
}
