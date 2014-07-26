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
#include <simplicity/common/Category.h>
#include <simplicity/logging/Logs.h>

#include "OpenGL.h"
#include "OpenGLShader.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLShader::OpenGLShader(Type type, Resource& source) :
			shader(0),
			source(source.getData()),
			type(type)
		{
		}

		OpenGLShader::~OpenGLShader()
		{
			// TODO Clean up the shader?
		}

		GLuint OpenGLShader::getShader()
		{
			return shader;
		}

		void OpenGLShader::init()
		{
			if (type == Type::FRAGMENT)
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				OpenGL::checkError();
			}
			else if (type == Type::GEOMETRY)
			{
				shader = glCreateShader(GL_GEOMETRY_SHADER);
				OpenGL::checkError();
			}
			else if (type == Type::VERTEX)
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
				OpenGL::checkError();
			}

			const char* sourcePtr = source.data();
			const int sourceLength = -1;
			glShaderSource(shader, 1, &sourcePtr, &sourceLength);
			OpenGL::checkError();

			glCompileShader(shader);
			OpenGL::checkError();

			GLint compileStatus;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
			OpenGL::checkError();

			if (compileStatus == 0)
			{
				GLchar infoLog[1024];
				glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
				OpenGL::checkError();

				Logs::log(Category::ERROR_LOG, "Error compiling shader:");
				Logs::log(Category::ERROR_LOG, infoLog);
			}
		}
	}
}
