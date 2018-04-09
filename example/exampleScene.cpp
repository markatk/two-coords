/**
 * Project: Two-Coords
 * File: example/exampleScene.cpp
 * Created: 06.03.2018
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

#include "exampleScene.h"

#include <spdlog/spdlog.h>

ExampleScene::ExampleScene() : twoCoords::Scene(glm::vec3(0.2f)) {
    resourceManager()->addDirectory("assets", true);

    // create player
    _player = std::make_shared<twoCoords::SceneObject>(resourceManager()->texture("prototype_player.tga"), glm::vec2(400, 300));
    _player->setLayer(2);
    rootNode()->add(_player);

    _sound = std::make_shared<twoCoords::SceneSound>(resourceManager()->soundBuffer("helloworld.wav"));
    _sound->setLooping(true);
	// rootNode()->add(_sound);

	_button = std::make_shared<twoCoords::SceneButton>(resourceManager()->texture("prototype_button.tga"), resourceManager()->texture("prototype_button.tga"), 123);
	rootNode()->add(_button);

	auto tileMap = std::make_shared<twoCoords::TileMap>(64, 64, 9);
	tileMap->row(0, 1);
	tileMap->row(tileMap->height() - 1, 17);
	tileMap->column(0, 8);
	tileMap->column(tileMap->width() - 1, 10);
	tileMap->set(0, 0, 0);
	tileMap->set(tileMap->width() - 1, 0, 2);
	tileMap->set(0, tileMap->height() - 1, 16);
	tileMap->set(tileMap->width() - 1, tileMap->height() - 1, 18);

	_background = std::make_shared<twoCoords::SceneMap>(resourceManager()->textureMap("tiles-001.png", 32, 32), tileMap, glm::vec2(256, 256));
	rootNode()->add(_background);
}

ExampleScene::~ExampleScene() {

}

void ExampleScene::enter() {
	_sound->play();
}

void ExampleScene::update() {
	// move player
	glm::vec2 pos = _player->position();
	float speed = 50.0f / 1000.0f;

	if (key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed *= 2;
	}

	if (key(GLFW_KEY_W) == GLFW_PRESS) {
		pos.y -= speed;
	}

	if (key(GLFW_KEY_S) == GLFW_PRESS) {
		pos.y += speed;
	}

	if (key(GLFW_KEY_A) == GLFW_PRESS) {
		pos.x -= speed;
	}

	if (key(GLFW_KEY_D) == GLFW_PRESS) {
		pos.x += speed;
	}

	_player->setPosition(pos);
	camera()->setPosition(pos - glm::vec2(400, 300));

	// update engine
	twoCoords::Scene::update();
}

void ExampleScene::key_callback(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			window()->close();
		}
	}
}

void ExampleScene::button_callback(std::shared_ptr<twoCoords::SceneButton> button, int action) {
	spdlog::get("console")->info("Button " + std::to_string(button->identifier()) + " action " + std::to_string(action));
}
