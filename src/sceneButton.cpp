/**
 * Project: Two-Coords
 * File: src/sceneButton.cpp
 * Created: 24.03.2018
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

#include "sceneButton.h"

#include "texture.h"
#include "scene.h"

#include <GLFW/glfw3.h>

twoCoords::SceneButton::SceneButton(std::shared_ptr<Texture> texture, std::shared_ptr<Texture> clickedTexture, int identifier, glm::vec2 position) : SceneGUIObject(texture, identifier, position) {
    _defaultTexture = texture;
    _clickedTexture = clickedTexture;
    _hoverTexture = nullptr;
}

twoCoords::SceneButton::~SceneButton() {

}

void twoCoords::SceneButton::setDefaultTexture(std::shared_ptr<Texture> texture) {
    _defaultTexture = texture;
}

void twoCoords::SceneButton::setClickedTexture(std::shared_ptr<Texture> texture) {
    _clickedTexture = texture;
}

void twoCoords::SceneButton::setHoverTexture(std::shared_ptr<Texture> texture) {
    _hoverTexture = texture;
}

std::shared_ptr<twoCoords::Texture> twoCoords::SceneButton::defaultTexture() const {
    return _defaultTexture;
}

std::shared_ptr<twoCoords::Texture> twoCoords::SceneButton::clickedTexture() const {
    return _clickedTexture;
}

std::shared_ptr<twoCoords::Texture> twoCoords::SceneButton::hoverTexture() const {
    return _hoverTexture;
}

void twoCoords::SceneButton::leftClicked(std::shared_ptr<Scene> scene) {
    if (_clickedTexture != nullptr) {
        setTexture(_clickedTexture);
    }

    scene->button_callback(std::static_pointer_cast<SceneButton>(shared_from_this()), BUTTON_ACTION_PRESSED);
}

void twoCoords::SceneButton::leftReleased(std::shared_ptr<Scene> scene) {
    if (isHovered() && _hoverTexture != nullptr) {
        setTexture(_hoverTexture);
    } else {
        setTexture(_defaultTexture);
    }

    scene->button_callback(std::static_pointer_cast<SceneButton>(shared_from_this()), BUTTON_ACTION_RELEASED);
}

void twoCoords::SceneButton::entered(std::shared_ptr<Scene> scene) {
    if (_hoverTexture != nullptr) {
        setTexture(_hoverTexture);
    }

    scene->button_callback(std::static_pointer_cast<SceneButton>(shared_from_this()), BUTTON_ACTION_ENTERED);
}

void twoCoords::SceneButton::exited(std::shared_ptr<Scene> scene) {
    setTexture(_defaultTexture);
    scene->button_callback(std::static_pointer_cast<SceneButton>(shared_from_this()), BUTTON_ACTION_EXITED);
}
