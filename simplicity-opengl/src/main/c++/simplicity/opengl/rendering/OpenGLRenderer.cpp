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
//#include <windows.h>

#include <GL/glew.h>
#include <GL/glu.h>

#include <simplicity/math/MathConstants.h>
#include <simplicity/math/MathFunctions.h>
#include <simplicity/math/Matrix.h>
#include <simplicity/model/Mesh.h>
#include <simplicity/model/shape/Capsule.h>
#include <simplicity/model/shape/Cylinder.h>
#include <simplicity/model/shape/Sphere.h>
#include <simplicity/model/shape/Torus.h>

#include "../model/OpenGLMesh.h"
#include "OpenGLRenderer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLRenderer::OpenGLRenderer() :
				clearColorBuffer(true),
				clearDepthBuffer(true),
				clearingColor(0.0f, 0.0f, 0.0f, 1.0f),
				clearStencilBuffer(true),
				pipeline()
		{
		}

		bool OpenGLRenderer::clearsColorBuffer() const
		{
			return clearColorBuffer;
		}

		bool OpenGLRenderer::clearsDepthBuffer() const
		{
			return clearDepthBuffer;
		}

		bool OpenGLRenderer::clearsStencilBuffer() const
		{
			return clearStencilBuffer;
		}

		void OpenGLRenderer::dispose()
		{
			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		}

		const Vector4& OpenGLRenderer::getClearingColor() const
		{
			return clearingColor;
		}

		int OpenGLRenderer::getOpenGLDrawingMode(Model::PrimitiveType primitiveType)
		{
			if (primitiveType == Model::POINTS)
			{
				return GL_POINTS;
			}
			else if (primitiveType == Model::LINE_LIST)
			{
				return GL_LINE;
			}
			else if (primitiveType == Model::LINE_STRIP)
			{
				return GL_LINE_STRIP;
			}
			else if (primitiveType == Model::TRIANGLE_LIST)
			{
				return GL_TRIANGLES;
			}
			else if (primitiveType == Model::TRIANGLE_STRIP)
			{
				return GL_TRIANGLE_STRIP;
			}

			return -1;
		}

		Pipeline* OpenGLRenderer::getDefaultPipeline()
		{
			return pipeline.get();
		}

		void OpenGLRenderer::init()
		{
			if (clearColorBuffer)
			{
				glClearColor(clearingColor.X(), clearingColor.Y(), clearingColor.Z(), clearingColor.W());
				glClear(GL_COLOR_BUFFER_BIT);
			}
			if (clearDepthBuffer)
			{
				glClear(GL_DEPTH_BUFFER_BIT);
			}
			if (clearStencilBuffer)
			{
				glClear(GL_STENCIL_BUFFER_BIT);
			}
		}

		bool OpenGLRenderer::isScissorEnabled() const
		{
			return glIsEnabled(GL_SCISSOR_TEST) == GL_TRUE;
		}

		void OpenGLRenderer::render(const Model& model)
		{
			if (model.getTypeID() == OpenGLMesh::TYPE_ID)
			{
				const OpenGLMesh& openGlMesh = static_cast<const OpenGLMesh&>(model);

				glBindVertexArray(openGlMesh.getVAO());

				glDrawElements(getOpenGLDrawingMode(openGlMesh.getPrimitiveType()), openGlMesh.getIndexCount(),
						GL_UNSIGNED_INT, 0);
			}
		}

		void OpenGLRenderer::setClearBuffers(bool clearBuffers)
		{
			clearColorBuffer = clearBuffers;
			clearDepthBuffer = clearBuffers;
			clearStencilBuffer = clearBuffers;
		}

		void OpenGLRenderer::setClearColorBuffer(bool clearColorBuffer)
		{
			this->clearColorBuffer = clearColorBuffer;
		}

		void OpenGLRenderer::setClearDepthBuffer(bool clearDepthBuffer)
		{
			this->clearDepthBuffer = clearDepthBuffer;
		}

		void OpenGLRenderer::setClearingColor(const Vector4& clearingColor)
		{
			this->clearingColor = clearingColor;
		}

		void OpenGLRenderer::setClearStencilBuffer(bool clearStencilBuffer)
		{
			this->clearStencilBuffer = clearStencilBuffer;
		}

		void OpenGLRenderer::setScissor(const Vector<unsigned int, 2>& topLeft,
				const Vector<unsigned int, 2>& bottomRight)
		{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			glScissor(topLeft.X(), viewport[3] - bottomRight.Y(), bottomRight.X() - topLeft.X(),
					bottomRight.Y() - topLeft.Y());
		}

		void OpenGLRenderer::setScissorEnabled(bool scissorEnabled)
		{
			if (scissorEnabled)
			{
				glEnable(GL_SCISSOR_TEST);
			}
			else
			{
				glDisable(GL_SCISSOR_TEST);
			}
		}

		void OpenGLRenderer::setDefaultPipeline(unique_ptr<Pipeline> pipeline)
		{
			this->pipeline = move(pipeline);
		}
	}
}
