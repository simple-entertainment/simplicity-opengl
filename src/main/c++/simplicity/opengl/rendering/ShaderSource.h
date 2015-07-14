/*
 * Copyright © 2015 Simple Entertainment Limited
 *
 * This file is part of The Simplicity Engine.
 *
 * The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef SHADERSOURCE_H_
#define SHADERSOURCE_H_

#include <string>

namespace simplicity
{
	namespace opengl
	{
		namespace ShaderSource
		{
			std::string fragmentSimple =
					"#version 330\n"

					"// /////////////////////////\n"
					"// Structures\n"
					"// /////////////////////////\n"

					"struct Point\n"
					"{\n"
					"	vec4 clipPosition;\n"
					"	vec4 color;\n"
					"	vec3 normal;\n"
					"	vec2 texCoord;\n"
					"	vec3 worldPosition;\n"
					"};\n"

					"// /////////////////////////\n"
					"// Variables\n"
					"// /////////////////////////\n"

					"in Point point;\n"

					"uniform sampler2D sampler;\n"
					"uniform int samplerEnabled;\n"

					"out vec4 color;\n"

					"// /////////////////////////\n"
					"// Shader\n"
					"// /////////////////////////\n"

					"void main()\n"
					"{\n"
					"	if (samplerEnabled == 1)\n"
					"	{\n"
					"		color = texture2D(sampler, point.texCoord);\n"
					"	}\n"
					"	else\n"
					"	{\n"
					"		color = point.color;\n"
					"	}\n"
					"}";

			std::string vertexClip =
					"#version 330\n"

					"// /////////////////////////\n"
					"// Structures\n"
					"// /////////////////////////\n"

					"struct Point\n"
					"{\n"
					"	vec4 clipPosition;\n"
					"	vec4 color;\n"
					"	vec3 normal;\n"
					"	vec2 texCoord;\n"
					"	vec3 worldPosition;\n"
					"};\n"

					"// /////////////////////////\n"
					"// Variables\n"
					"// /////////////////////////\n"

					"layout (location = 0) in vec4 color;\n"
					"layout (location = 1) in vec3 normal;\n"
					"layout (location = 2) in vec3 position;\n"
					"layout (location = 3) in vec2 texCoord;\n"

					"out Point point;\n"

					"// /////////////////////////\n"
					"// Shader\n"
					"// /////////////////////////\n"

					"void main()\n"
					"{\n"
					"	point.clipPosition = vec4(position, 1.0);\n"
					"	point.color = color;\n"
					"	point.normal = normal;\n"
					"	point.texCoord = texCoord;\n"
					"	point.worldPosition = position;\n"

					"	gl_Position = point.clipPosition;\n"
					"}";

			std::string vertexSimple =
					"#version 330\n"

					"// /////////////////////////\n"
					"// Structures\n"
					"// /////////////////////////\n"

					"struct Point\n"
					"{\n"
					"	vec4 clipPosition;\n"
					"	vec4 color;\n"
					"	vec3 normal;\n"
					"	vec2 texCoord;\n"
					"	vec3 worldPosition;\n"
					"};\n"

					"// /////////////////////////\n"
					"// Variables\n"
					"// /////////////////////////\n"

					"layout (location = 0) in vec4 color;\n"
					"layout (location = 1) in vec3 normal;\n"
					"layout (location = 2) in vec3 position;\n"
					"layout (location = 3) in vec2 texCoord;\n"

					"uniform mat4 cameraTransform;\n"
					"uniform mat4 worldTransform;\n"

					"out Point point;\n"

					"// /////////////////////////\n"
					"// Shader\n"
					"// /////////////////////////\n"

					"void main()\n"
					"{\n"
					"	vec4 worldPosition = worldTransform * vec4(position, 1.0);\n"
					"	vec4 clipPosition = cameraTransform * worldPosition;\n"

					"	mat4 worldRotation = worldTransform;\n"
					"	worldRotation[3][0] = 0.0f;\n"
					"	worldRotation[3][1] = 0.0f;\n"
					"	worldRotation[3][2] = 0.0f;\n"
					"	worldRotation[3][3] = 1.0f;\n"
					"	vec4 worldNormal = worldRotation * vec4(normal, 1.0f);\n"

					"	point.clipPosition = clipPosition;\n"
					"	point.color = color;\n"
					"	point.normal = worldNormal.xyz;\n"
					"	point.texCoord = texCoord;\n"
					"	point.worldPosition = worldPosition.xyz;\n"

					"	gl_Position = clipPosition;\n"
					"}";
		}
	}
}

#endif /* SHADERSOURCE_H_ */
