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
//#include <simplicity/math/MathFunctions.h>

#include "OpenGLCamera.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLCamera::OpenGLCamera() :
			farClippingDistance(1000.0f),
			frameHeight(0.0f),
			frameWidth(0.0f),
			nearClippingDistance(0.1f),
			projection()
		{
		}

		float OpenGLCamera::getFarClippingDistance() const
		{
			return farClippingDistance;
		}

		float OpenGLCamera::getFrameHeight() const
		{
			return frameHeight;
		}

		float OpenGLCamera::getFrameWidth() const
		{
			return frameWidth;
		}

		float OpenGLCamera::getNearClippingDistance() const
		{
			return nearClippingDistance;
		}

		const Matrix44& OpenGLCamera::getProjection() const
		{
			return projection;
		}

		void OpenGLCamera::setFarClippingDistance(float farClippingDistance)
		{
			this->farClippingDistance = farClippingDistance;
		}

		void OpenGLCamera::setNearClippingDistance(float nearClippingDistance)
		{
			this->nearClippingDistance = nearClippingDistance;
		}

		void OpenGLCamera::setOrthogonal(float width, float height)
		{
			// TODO Use OpenGL 3.x!!!
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glOrtho(-width / 2, width / 2, -height / 2, height / 2, nearClippingDistance, farClippingDistance);

			frameHeight = height;
			frameWidth = width;

			glMatrixMode(GL_MODELVIEW);
		}

		void OpenGLCamera::setPerspective(float yAxisFieldOfView, float aspectRatio)
		{
			float halfEdgeY = nearClippingDistance * tan(yAxisFieldOfView * MathConstants::PI / 360.0f);
			float halfEdgeX = halfEdgeY * aspectRatio;

			frameHeight = halfEdgeY * 2.0f;
			frameWidth = halfEdgeX * 2.0f;

			float depth = farClippingDistance - nearClippingDistance;
			float twoNearClippingDistance = 2.0f * nearClippingDistance;

			projection[0] = twoNearClippingDistance / frameWidth;
			projection[1] = 0.0f;
			projection[2] = 0.0f;
			projection[3] = 0.0f;
			projection[4] = 0.0f;
			projection[5] = twoNearClippingDistance / frameHeight;
			projection[6] = 0.0f;
			projection[7] = 0.0f;
			projection[8] = 0.0f; // (halfEdgeX + -halfEdgeX) / frameWidth;
			projection[9] = 0.0f; // (halfEdgeY + -halfEdgeY) / frameHeight;
			projection[10] = (nearClippingDistance + farClippingDistance) * -1.0f / depth;
			projection[11] = -1.0f;
			projection[12] = 0.0f;
			projection[13] = 0.0f;
			projection[14] = -twoNearClippingDistance * farClippingDistance / depth;
			projection[15] = 0.0f;
		}
	}
}
