/**
 * Project: Two-Coords
 * File: src/scene.cpp
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

#include "scene.h"

#include "sceneNode.h"
#include "window.h"
#include "resourceManager.h"
#include "camera.h"
#include "sceneManager.h"
#include "sceneGUIObject.h"

twoCoords::Scene::Scene(glm::vec3 backgroundColor) {
    _backgroundColor = backgroundColor;
    _rootNode = std::make_shared<SceneNode>();
    _resourceManager = std::make_shared<ResourceManager>();
    _camera = std::make_shared<Camera>();
}

twoCoords::Scene::~Scene() {
    
}

void twoCoords::Scene::update(float) {

}

void twoCoords::Scene::enter() {

}

void twoCoords::Scene::exit() {

}

bool twoCoords::Scene::isActive() const {
    auto window = _window.lock();
    if (window == nullptr) {
        return false;
    }

    return window->sceneManager()->currentScene() == shared_from_this();
}

void twoCoords::Scene::setBackgroundColor(glm::vec3 color) {
    _backgroundColor = color;
}

void twoCoords::Scene::setBackgroundColor(float red, float green, float blue) {
    _backgroundColor.x = red;
    _backgroundColor.y = green;
    _backgroundColor.z = blue;
}

glm::vec3 twoCoords::Scene::backgroundColor() const {
    return _backgroundColor;
}

int twoCoords::Scene::key(int key) const {
    auto window = _window.lock();
    if (window == nullptr) {
        return -1;
    }

    return glfwGetKey(window->windowHandle(), key);
}

int twoCoords::Scene::mouseButton(int button) const {
    auto window = _window.lock();
    if (window == nullptr) {
        return -1;
    }

    return glfwGetMouseButton(window->windowHandle(), button);
}

void twoCoords::Scene::setCursorPosition(glm::vec2 position) {
    auto window = _window.lock();
    if (window == nullptr) {
        return;
    }

    glfwSetCursorPos(window->windowHandle(), position.x, position.y);
}

glm::vec2 twoCoords::Scene::cursorPosition() const {
    auto window = _window.lock();
    if (window == nullptr) {
        return glm::vec2(-1, -1);
    }

    double x, y;
    glfwGetCursorPos(window->windowHandle(), &x, &y);
    return glm::vec2(x, y);
}

bool twoCoords::Scene::isJoystickConnected(int joystick) const {
    return glfwJoystickPresent(joystick) == GL_TRUE;
}

const float *twoCoords::Scene::joystickAxes(int joystick, int *count) const {
    return glfwGetJoystickAxes(joystick, count);
}

int twoCoords::Scene::joystickNumberOfAxes(int joystick) const {
    int count;
    glfwGetJoystickAxes(joystick, &count);
    return count;
}

const float twoCoords::Scene::joystickAxis(int joystick, int axis) const {
    // get axes
    int count;
    const float *axes = joystickAxes(joystick, &count);

    // get axis
    if (count < 0 || axis >= count) {
        return 0;
    }

    return axes[axis];
}

const unsigned char *twoCoords::Scene::joystickButtons(int joystick, int *count) const {
    return glfwGetJoystickButtons(joystick, count);
}

int twoCoords::Scene::joystickNumberOfButtons(int joystick) const {
    int count;
    glfwGetJoystickButtons(joystick, &count);
    return count;
}

const unsigned char twoCoords::Scene::joystickButton(int joystick, int button) const {
    // get buttons
    int count;
    const unsigned char *buttons = joystickButtons(joystick, &count);

    // get button
    if (button < 0 || button >= count) {
        return GLFW_RELEASE;
    }

    return buttons[button];
}

std::string twoCoords::Scene::joystickName(int joystick) const {
    return std::string(glfwGetJoystickName(joystick));
}

void twoCoords::Scene::key_callback(int key, int scancode, int action, int mods) {
    
}

void twoCoords::Scene::mouseButton_callback(int button, int action, int mods) {

}

void twoCoords::Scene::cursorPosition_callback(double x, double y) {

}

void twoCoords::Scene::scroll_callback(double x, double y) {
    
}

void twoCoords::Scene::button_callback(std::shared_ptr<SceneButton> button, int action) {
    
}

std::shared_ptr<twoCoords::SceneNode> twoCoords::Scene::rootNode() const {
    return _rootNode;
}

std::shared_ptr<twoCoords::ResourceManager> twoCoords::Scene::resourceManager() const {
    return _resourceManager;
}

std::shared_ptr<twoCoords::Camera> twoCoords::Scene::camera() const {
    return _camera;
}

std::shared_ptr<twoCoords::Window> twoCoords::Scene::window() const {
    return _window.lock();
}

void twoCoords::Scene::updateNode(std::shared_ptr<SceneNode> node) {
    auto guiNode = std::dynamic_pointer_cast<SceneGUIObject>(node);
    if (guiNode != nullptr) {
        guiNode->updateGUI(shared_from_this());
    }

    for (auto it = node->children().begin(); it != node->children().end(); it++) {
        updateNode(*it);
    }
}
