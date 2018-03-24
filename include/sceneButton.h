/**
 * Project: Two-Coords
 * File: include/sceneButton.h
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

#include "sceneGUIObject.h"

#define BUTTON_ACTION_PRESSED 0
#define BUTTON_ACTION_RELEASED 1
#define BUTTON_ACTION_ENTERED 2
#define BUTTON_ACTION_EXITED 3 

namespace twoCoords {
    class SceneButton : public SceneGUIObject {
    private:
        std::shared_ptr<Texture> _defaultTexture;
        std::shared_ptr<Texture> _clickedTexture;
        std::shared_ptr<Texture> _hoverTexture;

    public:
        SceneButton(std::shared_ptr<Texture> texture, std::shared_ptr<Texture> clickedTexture, int identifier, glm::vec2 position = glm::vec2(0));
        virtual ~SceneButton();

        void setDefaultTexture(std::shared_ptr<Texture> texture);
        void setClickedTexture(std::shared_ptr<Texture> texture);
        void setHoverTexture(std::shared_ptr<Texture> texture);
        std::shared_ptr<Texture> defaultTexture() const;
        std::shared_ptr<Texture> clickedTexture() const;
        std::shared_ptr<Texture> hoverTexture() const;

    protected:
        virtual void leftClicked(std::shared_ptr<Scene> scene) override;
        virtual void leftReleased(std::shared_ptr<Scene> scene) override;
        virtual void entered(std::shared_ptr<Scene> scene) override;
        virtual void exited(std::shared_ptr<Scene> scene) override;
    };
}
