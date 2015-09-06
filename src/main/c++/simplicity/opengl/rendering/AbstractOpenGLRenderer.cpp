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
#include <GL/glew.h>

#include <simplicity/rendering/RenderingFactory.h>

#include "../common/OpenGL.h"
#include "AbstractOpenGLRenderer.h"
#include "OpenGLPipeline.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		AbstractOpenGLRenderer::AbstractOpenGLRenderer() :
				clearColorBuffer(true),
				clearDepthBuffer(true),
				clearingColor(0.0f, 0.0f, 0.0f, 1.0f),
				clearStencilBuffer(true),
				pipeline()
		{
		}

		bool AbstractOpenGLRenderer::clearsColorBuffer() const
		{
			return clearColorBuffer;
		}

		bool AbstractOpenGLRenderer::clearsDepthBuffer() const
		{
			return clearDepthBuffer;
		}

		bool AbstractOpenGLRenderer::clearsStencilBuffer() const
		{
			return clearStencilBuffer;
		}

		void AbstractOpenGLRenderer::dispose()
		{
			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			OpenGL::checkError();
		}

		const Vector4& AbstractOpenGLRenderer::getClearingColor() const
		{
			return clearingColor;
		}

		int AbstractOpenGLRenderer::getOpenGLDrawingMode(MeshBuffer::PrimitiveType primitiveType)
		{
			if (primitiveType == MeshBuffer::PrimitiveType::POINTS)
			{
				return GL_POINTS;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::LINE_LIST)
			{
				return GL_LINE;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::LINE_STRIP)
			{
				return GL_LINE_STRIP;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::TRIANGLE_LIST)
			{
				return GL_TRIANGLES;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::TRIANGLE_STRIP)
			{
				return GL_TRIANGLE_STRIP;
			}

			return -1;
		}

		Pipeline* AbstractOpenGLRenderer::getDefaultPipeline()
		{
			return pipeline.get();
		}

		void AbstractOpenGLRenderer::init()
		{
			if (clearColorBuffer)
			{
				glClearColor(clearingColor.X(), clearingColor.Y(), clearingColor.Z(), clearingColor.W());
				OpenGL::checkError();
				glClear(GL_COLOR_BUFFER_BIT);
				OpenGL::checkError();
			}
			if (clearDepthBuffer)
			{
				glClear(GL_DEPTH_BUFFER_BIT);
				OpenGL::checkError();
			}
			if (clearStencilBuffer)
			{
				glClear(GL_STENCIL_BUFFER_BIT);
				OpenGL::checkError();
			}

			// Provide the default pipeline.
			if (pipeline == nullptr)
			{
				pipeline = RenderingFactory::createPipeline();
			}
		}

		bool AbstractOpenGLRenderer::isScissorEnabled() const
		{
			GLboolean enabled = glIsEnabled(GL_SCISSOR_TEST);
			OpenGL::checkError();

			return enabled == GL_TRUE;
		}

		void AbstractOpenGLRenderer::setClearBuffers(bool clearBuffers)
		{
			clearColorBuffer = clearBuffers;
			clearDepthBuffer = clearBuffers;
			clearStencilBuffer = clearBuffers;
		}

		void AbstractOpenGLRenderer::setClearColorBuffer(bool clearColorBuffer)
		{
			this->clearColorBuffer = clearColorBuffer;
		}

		void AbstractOpenGLRenderer::setClearDepthBuffer(bool clearDepthBuffer)
		{
			this->clearDepthBuffer = clearDepthBuffer;
		}

		void AbstractOpenGLRenderer::setClearingColor(const Vector4& clearingColor)
		{
			this->clearingColor = clearingColor;
		}

		void AbstractOpenGLRenderer::setClearStencilBuffer(bool clearStencilBuffer)
		{
			this->clearStencilBuffer = clearStencilBuffer;
		}

		void AbstractOpenGLRenderer::setScissor(const Vector2ui& topLeft, const Vector2ui& bottomRight)
		{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			OpenGL::checkError();

			glScissor(topLeft.X(), viewport[3] - bottomRight.Y(), bottomRight.X() - topLeft.X(),
					bottomRight.Y() - topLeft.Y());
			OpenGL::checkError();
		}

		void AbstractOpenGLRenderer::setScissorEnabled(bool scissorEnabled)
		{
			if (scissorEnabled)
			{
				glEnable(GL_SCISSOR_TEST);
				OpenGL::checkError();
			}
			else
			{
				glDisable(GL_SCISSOR_TEST);
				OpenGL::checkError();
			}
		}

		void AbstractOpenGLRenderer::setDefaultPipeline(unique_ptr<Pipeline> pipeline)
		{
			this->pipeline = move(pipeline);
		}
	}
}
