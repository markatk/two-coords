/**
 * Project: Two-Coords
 * File: include/sceneNode.h
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

#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace twoCoords {
  class ShaderProgram;
  class SceneNode;

  class SceneNode : public std::enable_shared_from_this<SceneNode> {
  protected:
    glm::vec2 _size;

  private:
    glm::vec2 _position;
    glm::vec2 _scale;
    unsigned int _layer;
    float _rotation;
    bool _hidden;

    std::shared_ptr<SceneNode> _parent;
    std::vector<std::shared_ptr<SceneNode>> _children;

  public:
    SceneNode(glm::vec2 position = glm::vec2(0.0));
    virtual ~SceneNode();

    virtual void render(std::shared_ptr<ShaderProgram> program);

    std::shared_ptr<SceneNode> parent() const;

    void setPosition(glm::vec2 position);
    void setPosition(float x, float y);
    glm::vec2 position() const;

    void setLayer(unsigned int layer);
    unsigned int layer() const;

    void setScale(glm::vec2 scale);
    void setScale(float x, float y);
    void setScale(float scale);
    glm::vec2 scale() const;

    void setRotation(float rotation);
    float rotation() const;

    void setHidden(bool hidden);
    bool isHidden() const;

    void add(std::shared_ptr<twoCoords::SceneNode> child);
    void remove(std::shared_ptr<twoCoords::SceneNode> child);
    const std::vector<std::shared_ptr<twoCoords::SceneNode>> &children() const;
    bool hasChildren() const;

    glm::vec2 worldPosition() const;
    glm::vec2 worldScale() const;
    glm::mat4 model() const;

  protected:
    virtual void refresh();

  private:
		glm::mat4 modelForChild() const;
  };
}
