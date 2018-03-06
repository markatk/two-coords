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
#include <memory>

namespace twoCoords {
  class Window;
  class Renderer;
  class SceneManager;

  typedef void (*windowSizeCallback_t)(std::shared_ptr<Window> window, int width, int height);
  typedef void (*windowCloseCallback_t)(std::shared_ptr<Window> window);
  typedef void (*windowRefreshCallback_t)(std::shared_ptr<Window> window);
  typedef void (*windowFocusCallback_t)(std::shared_ptr<Window> window, int focused);
  typedef void (*windowIconifyCallback_t)(std::shared_ptr<Window> window, int iconified);

  class Window : public std::enable_shared_from_this<Window> {
  private:
    GLFWwindow *_window;

    std::shared_ptr<Renderer> _renderer;
    std::shared_ptr<SceneManager> _sceneManager;

    double _lastUpdateTime;
    int _renderedFrames;
    int _lastFramesPerSecond;

    windowSizeCallback_t _sizeCallback;
    windowCloseCallback_t _closeCallback;
    windowRefreshCallback_t _refreshCallback;
    windowFocusCallback_t _focusCallback;
    windowIconifyCallback_t _iconifyCallback;

  public:
    Window(int width, int height, std::string title, GLFWmonitor *monitor = NULL);
    virtual ~Window();

    void update();
    void close();
    bool isOpen() const;

    int width() const;
    int height() const;

    void setScreenUnits(int x, int y);

    void setSizeCallback(windowSizeCallback_t callback);
    void setCloseCallback(windowCloseCallback_t callback);
    void setRefreshCallback(windowRefreshCallback_t callback);
    void setFocusCallback(windowFocusCallback_t callbackl);
    void setIconifyCallback(windowIconifyCallback_t callback);

    std::shared_ptr<Renderer> renderer() const;
    std::shared_ptr<SceneManager> sceneManager() const;

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
