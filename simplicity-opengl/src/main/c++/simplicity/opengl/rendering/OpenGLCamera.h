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
#ifndef OPENGLCAMERA_H_
#define OPENGLCAMERA_H_

#include <simplicity/rendering/Camera.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A camera implemented using OpenGL.
		 * </p>
		 */
		class SIMPLE_API OpenGLCamera : public Camera
		{
			public:
				OpenGLCamera();

				float getFarClippingDistance() const;

				float getFrameHeight() const;

				float getFrameWidth() const;

				float getNearClippingDistance() const;

				const Matrix44& getProjection() const;

				void setFarClippingDistance(float farClippingDistance);

				void setNearClippingDistance(float nearClippingDistance);

				void setOrthogonal(float width, float height);

				void setPerspective(float yAxisFieldOfView, float aspectRatio);

			private:
				float farClippingDistance;

				float frameHeight;

				float frameWidth;

				float nearClippingDistance;

				Matrix44 projection;
		};
	}
}

#endif /* OPENGLCAMERA_H_ */
