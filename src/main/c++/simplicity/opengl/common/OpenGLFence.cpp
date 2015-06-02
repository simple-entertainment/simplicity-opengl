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
#include "OpenGLFence.h"

const GLuint64 TIMEOUT = 1000000000; // One second.

namespace simplicity
{
	namespace opengl
	{
		OpenGLFence::OpenGLFence() :
			fence(glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0))
		{
			// Check for an error caused by the call to glFenceSync in the initializer list.
			OpenGL::checkError();
		}

		OpenGLFence::~OpenGLFence()
		{
			glDeleteSync(fence);
			OpenGL::checkError();
		}

		void OpenGLFence::wait() const
		{
			// First do a quick check.
			GLenum result = glClientWaitSync(fence, 0, 0);
			OpenGL::checkError();

			while (result == GL_TIMEOUT_EXPIRED)
			{
				// Now flush and wait...
				result = glClientWaitSync(fence, GL_SYNC_FLUSH_COMMANDS_BIT, TIMEOUT);
				OpenGL::checkError();
			}
		}
	}
}
