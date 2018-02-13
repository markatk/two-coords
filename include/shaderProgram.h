/**
 * Project: Two-Coords
 * File: include/shaderProgram.h
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

#pragma once

#include <vector>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace twoCoords {
  class Shader;

  class ShaderProgram {
  private:
    GLuint _object;

  public:
    ShaderProgram(const std::vector<Shader> &shaders);
    virtual ~ShaderProgram();

    void use() const;
    void stopUsing() const;
    bool isInUse() const;

    GLint attrib(const GLchar *name) const;
    GLint uniform(const GLchar *name) const;

    void setUniform(const GLchar *name, const glm::mat4 &matrix, GLboolean transpose = GL_FALSE);
    void setUniform(const GLchar *name, const GLuint value);

    GLuint object() const;

  private:
    // disable copying
    ShaderProgram(const ShaderProgram &);
    const ShaderProgram &operator=(const ShaderProgram &);
  };
}
