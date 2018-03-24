/**
 * Project: Two-Coords
 * File: src/sceneGUIObject.cpp
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

#include "sceneGUIObject.h"

#include "texture.h"

#include <GLFW/glfw3.h>

twoCoords::SceneGUIObject::SceneGUIObject(std::shared_ptr<Texture> texture, int identifier, glm::vec2 position) : SceneObject(texture, position) {
    _identifier = identifier;
    _hovered = false;
    _leftClicked = false;
    _rightClicked = false;
}

twoCoords::SceneGUIObject::~SceneGUIObject() {

}

void twoCoords::SceneGUIObject::setIdentifier(int identifier) {
    _identifier = identifier;
}

int twoCoords::SceneGUIObject::identifier() const {
    return _identifier;
}

bool twoCoords::SceneGUIObject::isLeftClicked() const {
    return _leftClicked;
}

bool twoCoords::SceneGUIObject::isRightClicked() const {
    return _rightClicked;
}

bool twoCoords::SceneGUIObject::isHovered() const {
    return _hovered;
}

void twoCoords::SceneGUIObject::leftClicked(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::leftReleased(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::rightClicked(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::rightReleased(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::entered(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::exited(std::shared_ptr<Scene> scene) {

}

void twoCoords::SceneGUIObject::updateGUI(std::shared_ptr<Scene> scene) {
    if (inside(scene->cursorPosition())) {
        // check mouse over
        if (_hovered == false) {
            _hovered = true;
            entered(scene);
        }

        // check mouse button clicks
        if (_leftClicked == false && scene->mouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            _leftClicked = true;
            leftClicked(scene);
        } else if (_leftClicked && scene->mouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
            _leftClicked = false;
            leftReleased(scene);
        }

        if (_rightClicked == false && scene->mouseButton(GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
            _rightClicked = true;
            rightClicked(scene);
        } else if (_rightClicked && scene->mouseButton(GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
            _rightClicked = false;
            rightReleased(scene);
        }

        return;
    }

    if (_hovered) {
        _hovered = false;
        exited(scene);
    }

    if (_leftClicked) {
        _leftClicked = false;
    }

    if (_rightClicked) {
        _rightClicked = false;
    }
}
