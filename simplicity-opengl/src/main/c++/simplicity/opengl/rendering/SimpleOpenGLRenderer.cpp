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

#include "../model/OpenGLMeshBuffer.h"
#include "OpenGL.h"
#include "SimpleOpenGLRenderer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		SimpleOpenGLRenderer::SimpleOpenGLRenderer() :
				clearColorBuffer(true),
				clearDepthBuffer(true),
				clearingColor(0.0f, 0.0f, 0.0f, 1.0f),
				clearStencilBuffer(true),
				pipeline()
		{
		}

		bool SimpleOpenGLRenderer::clearsColorBuffer() const
		{
			return clearColorBuffer;
		}

		bool SimpleOpenGLRenderer::clearsDepthBuffer() const
		{
			return clearDepthBuffer;
		}

		bool SimpleOpenGLRenderer::clearsStencilBuffer() const
		{
			return clearStencilBuffer;
		}

		void SimpleOpenGLRenderer::dispose()
		{
			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			OpenGL::checkError();
		}

		const Vector4& SimpleOpenGLRenderer::getClearingColor() const
		{
			return clearingColor;
		}

		int SimpleOpenGLRenderer::getOpenGLDrawingMode(Model::PrimitiveType primitiveType)
		{
			if (primitiveType == Model::PrimitiveType::POINTS)
			{
				return GL_POINTS;
			}
			else if (primitiveType == Model::PrimitiveType::LINE_LIST)
			{
				return GL_LINE;
			}
			else if (primitiveType == Model::PrimitiveType::LINE_STRIP)
			{
				return GL_LINE_STRIP;
			}
			else if (primitiveType == Model::PrimitiveType::TRIANGLE_LIST)
			{
				return GL_TRIANGLES;
			}
			else if (primitiveType == Model::PrimitiveType::TRIANGLE_STRIP)
			{
				return GL_TRIANGLE_STRIP;
			}

			return -1;
		}

		Pipeline* SimpleOpenGLRenderer::getDefaultPipeline()
		{
			return pipeline.get();
		}

		void SimpleOpenGLRenderer::init()
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
		}

		bool SimpleOpenGLRenderer::isScissorEnabled() const
		{
			GLboolean enabled = glIsEnabled(GL_SCISSOR_TEST);
			OpenGL::checkError();

			return enabled == GL_TRUE;
		}

		void SimpleOpenGLRenderer::render(const MeshBuffer& buffer,
				const vector<pair<Model*, Matrix44>>& modelsAndTransforms)
		{
			const OpenGLMeshBuffer& openGLBuffer = static_cast<const OpenGLMeshBuffer&>(buffer);
			glBindVertexArray(openGLBuffer.getVAO());
			OpenGL::checkError();

			for (const pair<Model*, Matrix44>& modelAndTransform : modelsAndTransforms)
			{
				if (modelAndTransform.first->getTypeID() != Mesh::TYPE_ID)
				{
					continue;
				}

				const Mesh* mesh = static_cast<const Mesh*>(modelAndTransform.first);
				pipeline->set("worldTransform", modelAndTransform.second);

				if (buffer.isIndexed())
				{
					glDrawElementsBaseVertex(getOpenGLDrawingMode(mesh->getPrimitiveType()),
							buffer.getIndexCount(*mesh), GL_UNSIGNED_INT,
							reinterpret_cast<GLvoid*>(buffer.getBaseIndex(*mesh) * sizeof(unsigned int)),
							buffer.getBaseVertex(*mesh));
					OpenGL::checkError();
				}
				else
				{
					glDrawArrays(getOpenGLDrawingMode(mesh->getPrimitiveType()), buffer.getBaseVertex(*mesh),
							buffer.getVertexCount(*mesh));
					OpenGL::checkError();
				}
			}
		}

		void SimpleOpenGLRenderer::setClearBuffers(bool clearBuffers)
		{
			clearColorBuffer = clearBuffers;
			clearDepthBuffer = clearBuffers;
			clearStencilBuffer = clearBuffers;
		}

		void SimpleOpenGLRenderer::setClearColorBuffer(bool clearColorBuffer)
		{
			this->clearColorBuffer = clearColorBuffer;
		}

		void SimpleOpenGLRenderer::setClearDepthBuffer(bool clearDepthBuffer)
		{
			this->clearDepthBuffer = clearDepthBuffer;
		}

		void SimpleOpenGLRenderer::setClearingColor(const Vector4& clearingColor)
		{
			this->clearingColor = clearingColor;
		}

		void SimpleOpenGLRenderer::setClearStencilBuffer(bool clearStencilBuffer)
		{
			this->clearStencilBuffer = clearStencilBuffer;
		}

		void SimpleOpenGLRenderer::setScissor(const Vector<unsigned int, 2>& topLeft,
				const Vector<unsigned int, 2>& bottomRight)
		{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			OpenGL::checkError();

			glScissor(topLeft.X(), viewport[3] - bottomRight.Y(), bottomRight.X() - topLeft.X(),
					bottomRight.Y() - topLeft.Y());
			OpenGL::checkError();
		}

		void SimpleOpenGLRenderer::setScissorEnabled(bool scissorEnabled)
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

		void SimpleOpenGLRenderer::setDefaultPipeline(unique_ptr<Pipeline> pipeline)
		{
			this->pipeline = move(pipeline);
		}
	}
}
