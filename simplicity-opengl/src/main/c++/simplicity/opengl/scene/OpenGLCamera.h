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

#include <simplicity/scene/Camera.h>

/**
 * <p>
 * A viewpoint within a Scene rendered by a JOGL rendering environment. This implementation uses only simple camera
 * techniques and properties.
 * </p>
 *
 * <p>
 * The viewing frustum is the shape that contains all components of the Scene displayed when viewing through a
 * SimpleJOGLCamera. The following diagram shows the 'side' and 'front' views of a viewing frustum.
 * </p>
 *
 * <pre>
 *              _______
 *       /|    |\     /|
 *      / |    | \___/ |
 * _\  |  |    | |   | |
 *  /  |  |    | |___| |
 *      \ |    | /   \ |
 *       \|    |/_____\|
 *
 *   side        front
 * </pre>
 *
 * <p>
 * <b>Eye</b>
 * </p>
 *
 * <p>
 * The eye is the position of the viewer. The 'front' of the frustum in the context of this explanation is the
 * side of the frustum that is closest to the eye. In the 'side' view the eye is shown as the arrow to the left
 * of the frustum.
 * </p>
 *
 * <p>
 * <b>Near Clipping Plane</b>
 * </p>
 *
 * <p>
 * The near clipping plane is a plane in the <code>SceneGraph</code> a distance from the eye in front of which
 * the viewer cannot see i.e. all components of the <code>SceneGraph</code> nearer to the eye than the near
 * clipping plane will be clipped (not drawn). The area on the near clipping plane that constitutes a face of
 * the frustum is shown as the short vertical line in the 'side' view and the smaller rectangle in the 'front'
 * view. This face can be thought of as analogous to the screen and is referred to as the frame.
 * </p>
 *
 * <p>
 * <b>Far Clipping Plane</b>
 * </p>
 *
 * <p>
 * The far clipping plane is a plane in the <code>SceneGraph</code> a distance from the eye past which the
 * viewer cannot see i.e. all components of the <code>SceneGraph</code> further from the eye than the far
 * clipping plane will be clipped (not drawn). The area on the far clipping plane that constitutes a face of the
 * frustum is shown as the long vertical line in the 'side' view and the larger rectangle in the 'front' view.
 * </p>
 *
 * <p>
 * <b>Frame Position and Dimensions</b>
 * </p>
 *
 * <p>
 * The dimensions of the areas of the clipping planes that are used as faces of the frustum are calculated
 * automatically by the <code>SimpleJOGLCamera</code>. The diagonal lines in the diagram extend from the four
 * corners of the far clipping plane to the four corners of the near clipping plane and finally (by default)
 * converge at the eye. The frame can be moved on the <code>x</code> and <code>y</code> axis so that the eye no
 * longer resides at this convergence. Also, the aspect ratio of the frame (4:3 by default) can be changed.
 * </p>
 *
 * @author Gary Buyn
 */

namespace simplicity
{
	namespace opengl
	{
		class OpenGLCamera : public Camera
		{
			public:
				OpenGLCamera();

				float getFarClippingDistance() const;

				float getFrameHeight() const;

				float getFrameWidth() const;

				float getNearClippingDistance() const;

				const Matrix44& getProjection() const;

				Vector3 getTranslation() const;

				void lookAt(const Vector3& target, const Vector3& up);

				void setFarClippingDistance(float farClippingDistance);

				void setFrameHeight(float frameHeight);

				void setFrameWidth(float frameWidth);

				void setNearClippingDistance(float nearClippingDistance);

				void setOrthogonal(float width, float height);

				void setPerspective(float yAxisFieldOfView, float aspectRatio);

				void setTranslation(const Vector3& translation);

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
