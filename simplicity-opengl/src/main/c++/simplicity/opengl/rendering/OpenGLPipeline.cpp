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
#include <simplicity/messaging/Messages.h>
#include <simplicity/messaging/Subject.h>

#include "OpenGLPipeline.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLPipeline::OpenGLPipeline(unique_ptr<OpenGLShader> vertexShader,
				unique_ptr<OpenGLShader> fragmentShader) :
			fragmentShader(move(fragmentShader)),
			geometryShader(),
			initialized(false),
			program(0),
			vertexShader(move(vertexShader))
		{
		}

		OpenGLPipeline::OpenGLPipeline(unique_ptr<OpenGLShader> vertexShader,
				unique_ptr<OpenGLShader> geometryShader,
				unique_ptr<OpenGLShader> fragmentShader) :
			fragmentShader(move(fragmentShader)),
			geometryShader(move(geometryShader)),
			initialized(false),
			program(0),
			vertexShader(move(vertexShader))
		{
		}

		OpenGLPipeline::~OpenGLPipeline()
		{
			// TODO Clean up the program?
		}

		void OpenGLPipeline::apply()
		{
			if (!initialized)
			{
				init();
				initialized = true;
			}

			// TODO Only needed for debugging apparently...
			glValidateProgram(program);

			GLint ValidateStatus;
		    glGetProgramiv(program, GL_VALIDATE_STATUS, &ValidateStatus);
		    if (ValidateStatus == 0)
		    {
			    GLchar infoLog[1024];
				glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);

				Logs::log(Category::ERROR_LOG, "Error validating shader program:");
				Logs::log(Category::ERROR_LOG, infoLog);
		    }

			glUseProgram(program);
		}

		void OpenGLPipeline::init()
		{
			program = glCreateProgram();

			if (vertexShader != nullptr)
			{
				vertexShader->init();
				glAttachShader(program, vertexShader->getShader());
			}

			if (geometryShader != nullptr)
			{
				geometryShader->init();
				glAttachShader(program, geometryShader->getShader());
			}

			if (fragmentShader != nullptr)
			{
				fragmentShader->init();
				glAttachShader(program, fragmentShader->getShader());
			}

			glLinkProgram(program);

			GLint linkStatus;
			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			if (linkStatus == 0)
			{
			    GLchar infoLog[1024];
				glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);

				Logs::log(Category::ERROR_LOG, "Error linking shader program:");
				Logs::log(Category::ERROR_LOG, infoLog);
			}
		}

		void OpenGLPipeline::set(const string& name, float value)
		{
			glUniform1f(glGetUniformLocation(program, name.data()), value);
		}

		void OpenGLPipeline::set(const string& name, int value)
		{
			glUniform1i(glGetUniformLocation(program, name.data()), value);
		}

		void OpenGLPipeline::set(const string& name, const Matrix44& value)
		{
			glUniformMatrix4fv(glGetUniformLocation(program, name.data()), 1, GL_FALSE, value.getData());
		}

		void OpenGLPipeline::set(const string& name, const Vector2& value)
		{
			glUniform2fv(glGetUniformLocation(program, name.data()), 1, value.getData());
		}

		void OpenGLPipeline::set(const string& name, const Vector3& value)
		{
			glUniform3fv(glGetUniformLocation(program, name.data()), 1, value.getData());
		}

		void OpenGLPipeline::set(const string& name, const Vector4& value)
		{
			glUniform4fv(glGetUniformLocation(program, name.data()), 1, value.getData());
		}

		void OpenGLPipeline::set(const string& structName, const string& name, float value)
		{
			string qualifiedName = structName + "." + name;
			glUniform1f(glGetUniformLocation(program, qualifiedName.data()), value);
		}

		void OpenGLPipeline::set(const string& structName, const string& name, int value)
		{
			string qualifiedName = structName + "." + name;
			glUniform1i(glGetUniformLocation(program, qualifiedName.data()), value);
		}

		void OpenGLPipeline::set(const string& structName, const string& name, const Matrix44& value)
		{
			string qualifiedName = structName + "." + name;
			glUniformMatrix4fv(glGetUniformLocation(program, qualifiedName.data()), 1, GL_FALSE, value.getData());
		}

		void OpenGLPipeline::set(const string& structName, const string& name, const Vector2& value)
		{
			string qualifiedName = structName + "." + name;
			glUniform2fv(glGetUniformLocation(program, qualifiedName.data()), 1, value.getData());
		}

		void OpenGLPipeline::set(const string& structName, const string& name, const Vector3& value)
		{
			string qualifiedName = structName + "." + name;
			glUniform3fv(glGetUniformLocation(program, qualifiedName.data()), 1, value.getData());
		}

		void OpenGLPipeline::set(const string& structName, const string& name, const Vector4& value)
		{
			string qualifiedName = structName + "." + name;
			glUniform4fv(glGetUniformLocation(program, qualifiedName.data()), 1, value.getData());
		}
	}
}
