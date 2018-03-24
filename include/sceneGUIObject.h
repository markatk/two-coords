/**
 * Project: Two-Coords
 * File: include/sceneGUIObject.h
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

#pragma once

#include "sceneObject.h"

#include "scene.h"

namespace twoCoords {
    class SceneGUIObject : public SceneObject {
    private:
        bool _hovered;
        bool _leftClicked;
        bool _rightClicked;
        int _identifier;

    public:
        SceneGUIObject(std::shared_ptr<Texture>, int identifier = 0, glm::vec2 position = glm::vec2(0));
        virtual ~SceneGUIObject();

        void setIdentifier(int identifier);
        int identifier() const;

        bool isLeftClicked() const;
        bool isRightClicked() const;
        bool isHovered() const;

    protected:
        virtual void leftClicked(std::shared_ptr<Scene> scene);
        virtual void leftReleased(std::shared_ptr<Scene> scene);
        virtual void rightClicked(std::shared_ptr<Scene> scene);
        virtual void rightReleased(std::shared_ptr<Scene> scene);
        virtual void entered(std::shared_ptr<Scene> scene);
        virtual void exited(std::shared_ptr<Scene> scene);

    private:
        void updateGUI(std::shared_ptr<Scene> scene);

        friend Scene;
    };
}
