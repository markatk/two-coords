/**
 * Project: Two-Coords
 * File: include/textShader.h
 * Created: 25.04.2018
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

namespace twoCoords {
    const char *TEXT_VERTEX_SHADER = R"(
		#version 150

		uniform mat4 projection;
		uniform mat4 model;

		in vec3 vert;
		in vec2 vertTexCoord;
		in vec4 vertColor;

		out vec2 fragTexCoord;
		out vec4 fragColor;

		void main() {
			// Pass the tex coord straight through to the fragment shader
			fragTexCoord = vertTexCoord;
			fragColor = vertColor;

			// Apply all matrix transformations to vert
			gl_Position = projection * model * vec4(vert, 1);
		}
	)";

	const char *TEXT_FRAGMENT_SHADER = R"(
		#version 150

		uniform sampler2D tex;

		in vec2 fragTexCoord;
		in vec4 fragColor;

		out vec4 finalColor;

		void main() {
			// finalColor = fragColor * vec4(1, 1, 1, texture(tex, fragTexCoord).r);
			finalColor = vec4(1, 1, 1, texture(tex, fragTexCoord).r);
		}
	)";
}
