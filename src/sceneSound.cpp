/**
 * Project: Two-Coords
 * File: src/sceneSound.cpp
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

#include "sceneSound.h"

#include "soundBuffer.h"

twoCoords::SceneSound::SceneSound(std::shared_ptr<SoundBuffer> buffer, glm::vec2 position) : SceneNode(position), _buffer(buffer) {
    alGenSources(1, &_source);
    alSourcei(_source, AL_BUFFER, _buffer->buffer());

    // TODO: This needs more tuning
    alSourcef(_source, AL_REFERENCE_DISTANCE, 25);
    alSourcef(_source, AL_ROLLOFF_FACTOR, 2);
    
    refresh();
}

twoCoords::SceneSound::~SceneSound() {
    alDeleteSources(1, &_source);
}

void twoCoords::SceneSound::play() {
    if (isActive() == false) {
        return;
    }

    alSourcePlay(_source);
}

void twoCoords::SceneSound::pause() {
    alSourcePause(_source);
}

void twoCoords::SceneSound::stop() {
    alSourceStop(_source);
}

bool twoCoords::SceneSound::isPlaying() const {
    ALint state;
    alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

void twoCoords::SceneSound::setVolume(float volume) {
    alSourcef(_source, AL_GAIN, volume);
}

float twoCoords::SceneSound::volume() const {
    ALfloat gain;
    alGetSourcef(_source, AL_GAIN, &gain);
    return gain;
}

void twoCoords::SceneSound::setLooping(bool loop) {
    alSourcei(_source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

bool twoCoords::SceneSound::isLooping() const {
    ALint looping;
    alGetSourcei(_source, AL_LOOPING, &looping);
    return looping == AL_TRUE;
}

std::shared_ptr<twoCoords::SoundBuffer> twoCoords::SceneSound::buffer() const {
    return _buffer;
}

ALuint twoCoords::SceneSound::source() const {
    return _source;
}

void twoCoords::SceneSound::refresh() {
    if (isActive() == false) {
        if (isPlaying()) {
            pause();
        }
        return;
    }

    auto position = worldPosition();
    alSource3f(_source, AL_POSITION, position.x, position.y, 0);
}
