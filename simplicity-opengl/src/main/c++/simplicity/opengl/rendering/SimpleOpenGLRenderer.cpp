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
#include "SimpleOpenGLRenderer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		void SimpleOpenGLRenderer::dispose()
		{
			glPointSize(1.0f);
		}

		int SimpleOpenGLRenderer::getOpenGLDrawingMode(Model::PrimitiveType primitiveType)
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

		void SimpleOpenGLRenderer::init()
		{
			glPointSize(2.0f);
		}

		void SimpleOpenGLRenderer::render(const Capsule& model)
		{
			glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

			gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
				model.getLevelOfDetail(), model.getLevelOfDetail());

			glPushMatrix();
			{
				gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());

				Matrix44 transformation;
				MathFunctions::getTranslation3(transformation).Z() = model.getLength();

				glMultMatrixf(transformation.getData());

				gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
			}
			glPopMatrix();
		}

		void SimpleOpenGLRenderer::render(const Circle&)
		{
		}

		void SimpleOpenGLRenderer::render(const Cube&)
		{
		}

		void SimpleOpenGLRenderer::render(const Cylinder& model)
		{
			glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

			gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
				model.getLevelOfDetail(), model.getLevelOfDetail());

			glPushMatrix();
			{
				Matrix44 transformation;
				Vector4 rotationAxis;
				rotationAxis.Y() = 1.0f;
				MathFunctions::rotate(transformation, MathConstants::PI, rotationAxis);

				glMultMatrixf(transformation.getData());

				gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
			}
			glPopMatrix();

			glPushMatrix();
			{
				Matrix44 transformation;
				MathFunctions::getTranslation3(transformation).Z() = model.getLength();

				glMultMatrixf(transformation.getData());

				gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
			}
			glPopMatrix();
		}

		void SimpleOpenGLRenderer::render(const Line<2>&)
		{
		}

		void SimpleOpenGLRenderer::render(const Mesh& model)
		{
			const OpenGLMesh& openGlMesh = dynamic_cast<const OpenGLMesh&>(model);

			glBindBuffer(GL_ARRAY_BUFFER, openGlMesh.getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, openGlMesh.getIBO());

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glDrawElements(getOpenGLDrawingMode(model.getPrimitiveType()), model.getIndices().size(), GL_UNSIGNED_INT,
					0);

			glDisableVertexAttribArray(0);
		}

		void SimpleOpenGLRenderer::render(const Sphere& model)
		{
			glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

			gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
		}

		void SimpleOpenGLRenderer::render(const Text&)
		{
		}

		void SimpleOpenGLRenderer::render(const Torus&)
		{
		}
	}
}
