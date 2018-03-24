/**
 * Project: Two-Coords
 * File: include/twoCoords.h
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

#ifdef _WIN32
#ifdef TWOCOORDS_EXPORTS
#define TWOCOORDS_API __declspec(dllexport)
#else
#define TWOCOORDS_API __declspec(dllimport)
#endif
#else
#define TWOCOORDS_API
#endif

#include "version.h"
#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "shaderProgram.h"
#include "sceneManager.h"
#include "scene.h"
#include "sceneNode.h"
#include "bitmap.h"
#include "texture.h"
#include "sceneObject.h"
#include "resourceManager.h"
#include "camera.h"
#include "soundBuffer.h"

namespace twoCoords {
  TWOCOORDS_API bool initialize();
  TWOCOORDS_API void deinitialize();
}
