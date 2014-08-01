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
#ifndef PERSISTENTLYMAPPEDOPENGLBUFFER_H_
#define PERSISTENTLYMAPPEDOPENGLBUFFER_H_

#include "OpenGLBuffer.h"

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A persistently mapped OpenGL buffer.
		 * </p>
		 */
		class SIMPLE_API PersistentlyMappedOpenGLBuffer : public OpenGLBuffer
		{
			public:
				PersistentlyMappedOpenGLBuffer(DataType dataType, unsigned int size, const byte* initialData = nullptr,
						AccessHint accessHint = AccessHint::WRITE);

				~PersistentlyMappedOpenGLBuffer();

				AccessHint getAccessHint() const override;

				byte* getData(bool readable) override;

				const byte* getData() const override;

				DataType getDataType() const override;

				GLuint getName() const override;

				void releaseData() const override;

			private:
				AccessHint accessHint;

				byte* data;

				DataType dataType;

				GLuint name;

				GLenum getOpenGLBufferTarget() const;
		};
	}
}

#endif /* PERSISTENTLYMAPPEDOPENGLBUFFER_H_ */
