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
#include <memory>

#include "../rendering/OpenGL.h"
#include "PersistentlyMappedOpenGLBuffer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		PersistentlyMappedOpenGLBuffer::PersistentlyMappedOpenGLBuffer(DataType dataType, unsigned int size,
				const byte* initialData, AccessHint accessHint) :
						accessHint(accessHint),
						data(nullptr),
						dataType(dataType),
						name(0)
		{
			GLenum access = GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT;
			if (accessHint == AccessHint::READ)
			{
				access |= GL_MAP_READ_BIT;
			}
			else if (accessHint == AccessHint::READ_WRITE)
			{
				access |= GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
			}
			else if (accessHint == AccessHint::WRITE)
			{
				access |= GL_MAP_WRITE_BIT;
			}

			glGenBuffers(1, &name);
			OpenGL::checkError();
			glBindBuffer(getOpenGLBufferTarget(), name);
			OpenGL::checkError();
			glBufferStorage(getOpenGLBufferTarget(), size, initialData, access);
			OpenGL::checkError();

			data = static_cast<byte*>(glMapBufferRange(getOpenGLBufferTarget(), 0, size, access));
			OpenGL::checkError();
		}

		PersistentlyMappedOpenGLBuffer::~PersistentlyMappedOpenGLBuffer()
		{
			glDeleteBuffers(1, &name);
			OpenGL::checkError();
		}

		Buffer::AccessHint PersistentlyMappedOpenGLBuffer::getAccessHint() const
		{
			return accessHint;
		}

		byte* PersistentlyMappedOpenGLBuffer::getData(bool /* readable */)
		{
			const byte* data = static_cast<const PersistentlyMappedOpenGLBuffer*>(this)->getData();
			return const_cast<byte*>(data);
		}

		const byte* PersistentlyMappedOpenGLBuffer::getData() const
		{
			// TODO Fencing... ?

			return data;
		}

		Buffer::DataType PersistentlyMappedOpenGLBuffer::getDataType() const
		{
			return dataType;
		}

		GLuint PersistentlyMappedOpenGLBuffer::getName() const
		{
			return name;
		}

		GLenum PersistentlyMappedOpenGLBuffer::getOpenGLBufferTarget() const
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

		void PersistentlyMappedOpenGLBuffer::releaseData() const
		{
		}
	}
}
