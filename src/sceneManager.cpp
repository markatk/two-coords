/**
 * Project: Two-Coords
 * File: src/sceneManager.cpp
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

#include "sceneManager.h"

#include "scene.h"
#include "window.h"
#include "sceneNode.h"

twoCoords::SceneManager::SceneManager(std::shared_ptr<Window> window) {
    _window = window;
}

twoCoords::SceneManager::~SceneManager() {

}

void twoCoords::SceneManager::pushScene(std::shared_ptr<twoCoords::Scene> scene) {
    // unload last scene
    if (isEmpty() == false) {
        auto lastScene = _scenes.back();
        lastScene->exit();
    }

    // load new scene
    _scenes.push_back(scene);
    scene->_window = window();
    scene->rootNode()->setActive(true);
    scene->enter();
}

std::shared_ptr<twoCoords::Scene> twoCoords::SceneManager::popScene() {
    // get current scene
    if (isEmpty()) {
        return nullptr;
    }

    auto scene = _scenes.back();
    _scenes.pop_back();
    scene->exit();
    scene->_window.reset();
    scene->rootNode()->setActive(false);

    return scene;
}

std::shared_ptr<twoCoords::Scene> twoCoords::SceneManager::currentScene() const {
    if (isEmpty()) {
        return nullptr;
    }

    return _scenes.back();
}

bool twoCoords::SceneManager::isEmpty() const {
    return _scenes.empty();
}

int twoCoords::SceneManager::count() const {
    return _scenes.size();
}

std::shared_ptr<twoCoords::Window> twoCoords::SceneManager::window() const {
    return _window.lock();
}
