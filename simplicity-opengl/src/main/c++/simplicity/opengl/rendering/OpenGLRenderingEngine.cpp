/*
 * Copyright © 2011 Simple Entertainment Limited
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
#include <algorithm>

#include <GL/glew.h>

#include <simplicity/common/AddressEquals.h>
#include <simplicity/math/Intersection.h>
#include <simplicity/math/MathFunctions.h>
#include <simplicity/rendering/Camera.h>
#include <simplicity/rendering/Light.h>
#include <simplicity/Simplicity.h>

#include "../model/OpenGLMeshBuffer.h"
#include "OpenGL.h"
#include "OpenGLRenderingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		void OpenGLRenderingEngine::bind(const MeshBuffer& buffer)
		{
			const OpenGLMeshBuffer& openGLBuffer = static_cast<const OpenGLMeshBuffer&>(buffer);

			glBindVertexArray(openGLBuffer.getVAO());
			OpenGL::checkError();
		}

		void OpenGLRenderingEngine::dispose()
		{
			// Revert depth test settings.
			glDepthFunc(GL_LESS);
			OpenGL::checkError();
			glDisable(GL_DEPTH_TEST);
			OpenGL::checkError();

			// Revert face culling settings.
			glDisable(GL_CULL_FACE);
			OpenGL::checkError();

			// Revert blending settings.
			glBlendFunc(GL_ONE, GL_ZERO);
			OpenGL::checkError();
			glDisable(GL_BLEND);
			OpenGL::checkError();
		}

		void OpenGLRenderingEngine::init()
		{
			// Ensure objects further from the viewpoint are not drawn over the top of closer objects. To assist multi
			// pass rendering, objects at the exact same distance can be rendered over (i.e. the object will be rendered
			// using the result of the last Renderer executed).
			glDepthFunc(GL_LEQUAL);
			OpenGL::checkError();
			glEnable(GL_DEPTH_TEST);
			OpenGL::checkError();

			// Only render the front (counter-clockwise) side of a polygon.
			glEnable(GL_CULL_FACE);
			OpenGL::checkError();

			// Enable blending for rendering transparency.
			glEnable(GL_BLEND);
			OpenGL::checkError();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			OpenGL::checkError();
		}

		void OpenGLRenderingEngine::postAdvance()
		{
		}

		bool OpenGLRenderingEngine::preAdvance()
		{
			// If we are using FreeGLUT the window may have been closed during this frame.
			// This is a bit ugly but we need to check for it since OpenGL would no longer be available.
			return Simplicity::isPlaying();
		}
	}
}
