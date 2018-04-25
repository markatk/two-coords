/**
 * Project: Two-Coords
 * File: include/resourceManager.h
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

#pragma once

#include <vector>
#include <string>
#include <memory>

namespace twoCoords {
    class Resource;
    class Texture;
    class TextureMap;
    class SoundBuffer;
    class Font;

    class ResourceManager {
    private:
        std::vector<std::shared_ptr<Resource>> _resources;

        std::vector<std::string> _textureExtensionFilter;
        std::vector<std::string> _soundExtensionFilter;
        std::vector<std::string> _fontExtensionFilter;

    public:
        ResourceManager();
        virtual ~ResourceManager();

        bool addFile(std::string filePath);
        void addDirectory(std::string directoryPath, bool recursive = false);

        bool preloadResources() const;

        std::shared_ptr<Texture> texture(std::string name);
        std::shared_ptr<TextureMap> textureMap(std::string name, int tileWidth, int tileHeight);
        std::shared_ptr<SoundBuffer> soundBuffer(std::string name);
        std::shared_ptr<Font> font(std::string name, int size);

    private:
        bool fileMatchesExtensionFilter(std::string extension) const;
        bool fileMatchesExtensionFilter(std::string extension, std::vector<std::string> filter) const;

        std::string filename(std::string filePath) const;
    };
}