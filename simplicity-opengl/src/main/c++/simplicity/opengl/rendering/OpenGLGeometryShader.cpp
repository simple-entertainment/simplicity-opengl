/*
 * Copyright © 2014 Simple Entertainment Limited
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
#include <simplicity/entity/Categories.h>
#include <simplicity/logging/Logs.h>

#include "OpenGLGeometryShader.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLGeometryShader::OpenGLGeometryShader(Resource& source) :
			shader(0),
			source(source.getData())
		{
		}

		OpenGLGeometryShader::~OpenGLGeometryShader()
		{
		}

		GLuint OpenGLGeometryShader::getShader()
		{
			return shader;
		}

		void OpenGLGeometryShader::init()
		{
			// TODO A bit too much code duplication in the different shader types for my liking... consider extracting
			// a super class.
			shader = glCreateShader(GL_GEOMETRY_SHADER);

			const char* sourcePtr = source.data();
			const int sourceLength = -1;
			glShaderSource(shader, 1, &sourcePtr, &sourceLength);

			glCompileShader(shader);

			GLint compileStatus;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
			if (compileStatus == 0)
			{
			    GLchar infoLog[1024];
			    glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);

			    Logs::log(Categories::ERROR, "Error compiling geometry shader:");
			    Logs::log(Categories::ERROR, infoLog);
			}
		}
	}
}
