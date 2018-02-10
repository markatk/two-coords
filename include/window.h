/**
 * Project: Two-Coords
 * File: include/window.h
 * Created: 10.02.2018
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
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace twoCoords {
  class Window {
  private:
  GLFWwindow *_window;

  public:
    Window(int width, int height, std::string title, GLFWmonitor *monitor = NULL);
    virtual ~Window();

    void update() const;
    void close();
    bool isOpen() const;

    int width() const;
    int height() const;

  private:
    static void windowSizeCallback(GLFWwindow *window, int width, int height);
    static void windowCloseCallback(GLFWwindow *window);
    static void windowRefreshCallback(GLFWwindow *window);
    static void windowFocusCallback(GLFWwindow *window, int focused);
    static void windowIconifyCallback(GLFWwindow *window, int iconified);

    // disable copying
    Window(const Window &);
    const Window &operator=(const Window &);
  };
}
