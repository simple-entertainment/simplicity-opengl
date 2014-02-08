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
				shader()
		{
		}

		bool OpenGLRenderer::clearsColorBuffer()
		{
			return clearColorBuffer;
		}

		bool OpenGLRenderer::clearsDepthBuffer()
		{
			return clearDepthBuffer;
		}

		bool OpenGLRenderer::clearsStencilBuffer()
		{
			return clearStencilBuffer;
		}

		void OpenGLRenderer::dispose()
		{
			glPointSize(1.0f);

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

		Shader* OpenGLRenderer::getShader()
		{
			return shader.get();
		}

		void OpenGLRenderer::init()
		{
			glPointSize(2.0f);

			if (clearColorBuffer)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(clearingColor.X(), clearingColor.Y(), clearingColor.Z(), clearingColor.W());
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

		void OpenGLRenderer::render(const Box&)
		{
		}

		void OpenGLRenderer::render(const Capsule& model)
		{
			glColor4f(model.getColor().R(), model.getColor().G(), model.getColor().B(), model.getColor().A());

			gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
				model.getLevelOfDetail(), model.getLevelOfDetail());

			glPushMatrix();
			{
				gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());

				Matrix44 transform;
				transform.setIdentity();
				Vector4 position = getPosition4(transform);
				position.Z() = model.getLength();
				setPosition(transform, position);

				glMultMatrixf(transform.getData());

				gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
			}
			glPopMatrix();
		}

		void OpenGLRenderer::render(const Circle&)
		{
		}

		void OpenGLRenderer::render(const Cube&)
		{
		}

		void OpenGLRenderer::render(const Cylinder& model)
		{
			glColor4f(model.getColor().R(), model.getColor().G(), model.getColor().B(), model.getColor().A());

			gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
				model.getLevelOfDetail(), model.getLevelOfDetail());

			glPushMatrix();
			{
				Matrix44 transform;
				transform.setIdentity();
				Vector4 rotationAxis;
				rotationAxis.Y() = 1.0f;
				rotate(transform, MathConstants::PI, rotationAxis);

				glMultMatrixf(transform.getData());

				gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
			}
			glPopMatrix();

			glPushMatrix();
			{
				Matrix44 transform;
				transform.setIdentity();
				Vector4 position = getPosition4(transform);
				position.Z() = model.getLength();
				setPosition(transform, position);

				glMultMatrixf(transform.getData());

				gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
			}
			glPopMatrix();
		}

		void OpenGLRenderer::render(const Line&)
		{
		}

		void OpenGLRenderer::render(const Mesh& model)
		{
			const OpenGLMesh& openGlMesh = dynamic_cast<const OpenGLMesh&>(model);

			glBindVertexArray(openGlMesh.getVAO());

			glDrawElements(getOpenGLDrawingMode(model.getPrimitiveType()), model.getIndices().size(), GL_UNSIGNED_INT,
					0);
		}

		void OpenGLRenderer::render(const Point& model)
		{
		}

		void OpenGLRenderer::render(const Sphere& model)
		{
			glColor4f(model.getColor().R(), model.getColor().G(), model.getColor().B(), model.getColor().A());

			gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
		}

		void OpenGLRenderer::render(const Square&)
		{
		}

		void OpenGLRenderer::render(const Text&)
		{
		}

		void OpenGLRenderer::render(const Torus&)
		{
		}

		void OpenGLRenderer::render(const Triangle&)
		{
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

		void OpenGLRenderer::setShader(unique_ptr<Shader> shader)
		{
			this->shader.release();
			this->shader.swap(shader);
		}
	}
}
