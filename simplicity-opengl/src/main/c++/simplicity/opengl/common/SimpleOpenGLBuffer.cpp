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
#include "OpenGL.h"
#include "SimpleOpenGLBuffer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		SimpleOpenGLBuffer::SimpleOpenGLBuffer(DataType dataType, unsigned int size, const byte* initialData,
				AccessHint accessHint) :
						accessHint(accessHint),
						dataType(dataType),
						name(0)
		{
			GLenum usage = GL_STATIC_DRAW;
			if (accessHint == AccessHint::READ)
			{
				usage = GL_STATIC_READ;
			}
			else if (accessHint == AccessHint::READ_WRITE)
			{
				usage = GL_DYNAMIC_READ;
			}
			else if (accessHint == AccessHint::WRITE)
			{
				usage = GL_DYNAMIC_DRAW;
			}

			glGenBuffers(1, &name);
			OpenGL::checkError();
			glBindBuffer(getOpenGLBufferTarget(), name);
			OpenGL::checkError();
			glBufferData(getOpenGLBufferTarget(), size, initialData, usage);
			OpenGL::checkError();
		}

		SimpleOpenGLBuffer::~SimpleOpenGLBuffer()
		{
			glDeleteBuffers(1, &name);
			OpenGL::checkError();
		}

		Buffer::AccessHint SimpleOpenGLBuffer::getAccessHint() const
		{
			return accessHint;
		}

		byte* SimpleOpenGLBuffer::getData(bool readable)
		{
			GLenum access = GL_WRITE_ONLY;
			if (readable)
			{
				access = GL_READ_WRITE;
			}

			glBindBuffer(getOpenGLBufferTarget(), name);
			OpenGL::checkError();
			GLvoid* data = glMapBuffer(getOpenGLBufferTarget(), access);
			OpenGL::checkError();

			return static_cast<byte*>(data);
		}

		const byte* SimpleOpenGLBuffer::getData() const
		{
			glBindBuffer(getOpenGLBufferTarget(), name);
			OpenGL::checkError();
			GLvoid* data = glMapBuffer(getOpenGLBufferTarget(), GL_READ_ONLY);
			OpenGL::checkError();

			return static_cast<byte*>(data);
		}

		Buffer::DataType SimpleOpenGLBuffer::getDataType() const
		{
			return dataType;
		}

		GLuint SimpleOpenGLBuffer::getName() const
		{
			return name;
		}

		GLenum SimpleOpenGLBuffer::getOpenGLBufferTarget() const
		{
			if (dataType == DataType::INDICES)
			{
				return GL_ELEMENT_ARRAY_BUFFER;
			}

			if (dataType == DataType::SHADER_DATA)
			{
				return GL_UNIFORM_BUFFER;
			}

			if (dataType == DataType::VERTICES)
			{
				return GL_ARRAY_BUFFER;
			}

			return 0;
		}

		void SimpleOpenGLBuffer::releaseData() const
		{
			glUnmapBuffer(getOpenGLBufferTarget());
			OpenGL::checkError();
		}
	}
}
