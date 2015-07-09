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
#include "DefaultShaderSource.h"

std::string defaultFragmentShaderSource =
		"#version 330\n"

		"// /////////////////////////\n"
		"// Structures\n"
		"// /////////////////////////\n"

		"struct Light\n"
		"{\n"
		"	vec4 ambient;\n"
		"	vec3 attenuation;\n"
		"	vec4 diffuse;\n"
		"	vec3 direction;\n"
		"	vec3 position;\n"
		"	float range;\n"
		"	vec4 specular;\n"
		"	float strength;\n"
		"};\n"

		"struct Point\n"
		"{\n"
		"	vec4 clipPosition;\n"
		"	vec4 color;\n"
		"	vec3 normal;\n"
		"	vec2 texCoord;\n"
		"	vec3 worldPosition;\n"
		"};\n"

		"// /////////////////////////\n"
		"// Functions\n"
		"// /////////////////////////\n"

		"vec4 applyDirectionalLight(Point point, Light light, vec3 cameraPosition)\n"
		"{\n"
		"	// Add the ambient term.\n"
		"	vec4 color = point.color * light.ambient;\n"

		"	float diffuseFactor = dot(-light.direction, point.normal);\n"
		"	if(diffuseFactor > 0.0f)\n"
		"	{\n"
		"		// Add the diffuse term.\n"
		"		color += diffuseFactor * point.color * light.diffuse;\n"

		"		// Add the specular term.\n"
		"		vec3 toCamera = normalize(cameraPosition - point.worldPosition);\n"
		"		vec3 lightReflect = normalize(reflect(light.direction, point.normal));\n"
		"		float specularFactor = dot(toCamera, lightReflect);\n"

		"		specularFactor = pow(specularFactor, light.strength);\n"
		"		if (specularFactor > 0.0f)\n"
		"		{\n"
		"			color += specularFactor * light.specular;\n"
		"		}\n"
		"	}\n"

		"	return color;\n"
		"}\n"

		"vec4 applyPointLight(Point point, Light light, vec3 cameraPosition)\n"
		"{\n"
		"	vec3 toLight = light.position - point.worldPosition;\n"
		"	float distanceToLight = length(toLight);\n"
		"	toLight /= distanceToLight;\n"

		"	// If the point is out of range, do not light it.\n"
		"	if(distanceToLight > light.range)\n"
		"	{\n"
		"		return vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
		"	}\n"

		"	// Add the ambient term.\n"
		"	vec4 color = point.color * light.ambient;\n"

		"	float diffuseFactor = dot(toLight, point.normal);\n"
		"	if(diffuseFactor > 0.0f)\n"
		"	{\n"
		"		// Add the diffuse term.\n"
		"		color += diffuseFactor * point.color * light.diffuse;\n"

		"		// Add the specular term.\n"
		"		vec3 toCamera = normalize(cameraPosition - point.worldPosition);\n"
		"		vec3 lightReflect = normalize(reflect(-toLight, point.normal));\n"
		"		float specularFactor = dot(toCamera, lightReflect);\n"

		"		specularFactor = pow(specularFactor, light.strength);\n"
		"		if (specularFactor > 0.0f)\n"
		"		{\n"
		"			color += specularFactor * light.specular;\n"
		"		}\n"
		"	}\n"

		"	// Attenuate\n"
		"	color /= dot(light.attenuation, vec3(1.0f, distanceToLight, distanceToLight * distanceToLight));\n"

		"	return color;\n"
		"}\n"

		"vec4 applySpotLight(Point point, Light light, vec3 cameraPosition)\n"
		"{\n"
		"	vec3 toLight = normalize(light.position - point.worldPosition);\n"

		"	return applyPointLight(point, light, cameraPosition) *\n"
		"		pow(max(dot(-toLight, light.direction), 0.0f), light.strength);\n"
		"}\n"

		"// /////////////////////////\n"
		"// Variables\n"
		"// /////////////////////////\n"

		"in Point point;\n"

		"uniform vec3 cameraPosition;\n"
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

std::string defaultVertexShaderSource =
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
