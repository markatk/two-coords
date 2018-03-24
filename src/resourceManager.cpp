/**
 * Project: Two-Coords
 * File: include/resourceManager.cpp
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

#include "resourceManager.h"

#include "resource.h"
#include "texture.h"
#include "soundBuffer.h"

#include <spdlog/spdlog.h>
#include <tinydir.h>

twoCoords::ResourceManager::ResourceManager() {
  _textureExtensionFilter.push_back(".tga");
  _textureExtensionFilter.push_back(".bmp");
  _textureExtensionFilter.push_back(".png");

  _soundExtensionFilter.push_back(".wav");
}

twoCoords::ResourceManager::~ResourceManager() {

}

bool twoCoords::ResourceManager::addFile(std::string filePath) {
  // get type of resource
  size_t pos = filePath.rfind(".");
  if (pos == std::string::npos) {
    return false;
  }

  std::string extension = filePath.substr(pos);
  if (fileMatchesExtensionFilter(extension) == false) {
    return false;
  }

  // check if resource is already loaded
  for (auto it = _resources.begin(); it != _resources.end(); it++) {
    if ((*it)->filePath() == filePath) {
      return true;
    }
  }

  // create new resource
  std::shared_ptr<Resource> resource = nullptr;

  if (fileMatchesExtensionFilter(extension, _textureExtensionFilter)) {
    resource = std::make_shared<Texture>(filePath);
  } else if (fileMatchesExtensionFilter(extension, _soundExtensionFilter)) {
    resource = std::make_shared<SoundBuffer>(filePath);
  }

  if (resource == nullptr) {
    return false;
  }

  // add resource to list
  _resources.push_back(resource);
  spdlog::get("console")->info("Add resource \"" + filePath + "\"");

  return true;
}

void twoCoords::ResourceManager::addDirectory(std::string directoryPath, bool recursive) {
  // get directory
  tinydir_dir dir;
  tinydir_open(&dir, directoryPath.c_str());

  while (dir.has_next) {
    // get next file
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0) {
      if (file.is_dir && recursive) {
        addDirectory(file.path, recursive);
      } else {
        addFile(file.path);
      }
    }

    // get next file
    tinydir_next(&dir);
  }

  tinydir_close(&dir);
}

bool twoCoords::ResourceManager::preloadResources() const {
  bool success = true;

  for (auto it = _resources.begin(); it != _resources.end(); it++) {
    if ((*it)->isLoaded()) {
      continue;
    }

    if ((*it)->load() == false) {
      success = false;
    }
  }

  return success;
}

std::shared_ptr<twoCoords::Texture> twoCoords::ResourceManager::texture(std::string name) {
  for (auto it = _resources.begin(); it != _resources.end(); it++) {
    if (filename((*it)->filePath()) != name) {
      continue;
    }

    if ((*it)->isLoaded() == false) {
      if ((*it)->load() == false) {
        return nullptr;
      }
    }

    return std::dynamic_pointer_cast<Texture>(*it);
  }

  spdlog::get("console")->warn("Texture not found for filename " + name);
  return nullptr;
}

std::shared_ptr<twoCoords::SoundBuffer> twoCoords::ResourceManager::soundBuffer(std::string name) {
  for (auto it = _resources.begin(); it != _resources.end(); it++) {
    if (filename((*it)->filePath()) != name) {
      continue;
    }

    if ((*it)->isLoaded() == false) {
      if ((*it)->load() == false) {
        return nullptr;
      }
    }

    return std::dynamic_pointer_cast<SoundBuffer>(*it);
  }

  spdlog::get("console")->warn("SoundBuffer not found for filename " + name);
  return nullptr;
}

bool twoCoords::ResourceManager::fileMatchesExtensionFilter(std::string extension) const {
  return fileMatchesExtensionFilter(extension, _textureExtensionFilter) || fileMatchesExtensionFilter(extension, _soundExtensionFilter);
}

bool twoCoords::ResourceManager::fileMatchesExtensionFilter(std::string extension, std::vector<std::string> filter) const {
  for (auto it = filter.begin(); it != filter.end(); it++) {
    if (*it == extension) {
      return true;
    }
  }

  return false;
}

std::string twoCoords::ResourceManager::filename(std::string filePath) const {
  size_t pos = filePath.find_last_of("\\/");
	if (pos == std::string::npos) {
		return filePath;
	}

	return filePath.substr(pos + 1);
}
