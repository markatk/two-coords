/**
 * Project: Two-Coords
 * File: include/scene.h
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

#include <memory>
#include <glm/glm.hpp>
#include <list>

namespace twoCoords {
    class SceneNode;
    class Window;
    class ResourceManager;
    class Camera;
    class SceneButton;
    class SceneManager;

    class Scene : public std::enable_shared_from_this<Scene> {
    private:
        std::shared_ptr<SceneNode> _rootNode;
        std::shared_ptr<ResourceManager> _resourceManager;
        std::shared_ptr<Camera> _camera;

        std::weak_ptr<Window> _window;

        glm::vec3 _backgroundColor;

    public:
        Scene(glm::vec3 backgroundColor = glm::vec3(0.0f));
        virtual ~Scene();

        virtual void update();
        virtual void enter();
        virtual void exit();
        bool isActive() const;

        void setBackgroundColor(glm::vec3 color);
        void setBackgroundColor(float red, float green, float blue);
        glm::vec3 backgroundColor() const;

        int key(int key) const;
        int mouseButton(int button) const;

        void setCursorPosition(glm::vec2 position);
        glm::vec2 cursorPosition() const;

        virtual void key_callback(int key, int scancode, int action, int mods);
        virtual void mouseButton_callback(int button, int action, int mods);
        virtual void cursorPosition_callback(double x, double y);
        virtual void scroll_callback(double x, double y);
        virtual void button_callback(std::shared_ptr<SceneButton> button, int action);

        std::shared_ptr<SceneNode> rootNode() const;
        std::shared_ptr<ResourceManager> resourceManager() const;
        std::shared_ptr<Camera> camera() const;
        std::shared_ptr<Window> window() const;
    
    private:
        void updateNode(std::shared_ptr<SceneNode> node);

        friend SceneManager;
    };
}
