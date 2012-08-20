/*
 * Copyright © Simple Entertainment Limited 2011
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
#ifndef OPENGLDEMO_H_
#define OPENGLDEMO_H_

#include <boost/any.hpp>

#include <simplicity/input/Button.h>
#include <simplicity/rendering/Light.h>

#include <simplicity/Demo.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * Provides common elements required by OpenGL demos.
		 * </p>
		 */
		class OpenGLDemo : public Demo
		{
			public:
				OpenGLDemo();

			protected:
				std::shared_ptr<Camera> addCamera();

				void addCapsule(TreeNode& parent);

				void addCylinder(TreeNode& parent);

				void addDescription(TreeNode& parent);

				void addLight();

				void addSphere(TreeNode& parent);

				void addTitle(TreeNode& parent);

				Torus& addTorus(TreeNode& parent);

				void dispose();

				std::shared_ptr<TreeNode> getModelsRoot();

				void init();

				void initScene() const;

				void removeAllEntities();

			private:
				std::vector<reference_wrapper<Entity> > entities;

				Button::State leftButtonState;

				/**
				 * <p>
				 * The root node of the scene (excluding the camera, light(s) and text).
				 * </p>
				 */
				std::shared_ptr<TreeNode> modelsRoot;

				/**
				 * <p>
				 * The current position of the mouse on the x axis.
				 * </p>
				 */
				int mouseX;

				/**
				 * <p>
				 * The current position of the mouse on the y axis.
				 * </p>
				 */
				int mouseY;

				std::shared_ptr<Model> createDescriptionLine(TreeNode& parent, const std::string& line,
					const unsigned int lineNum);

				virtual void onDispose() = 0;

				virtual void onInit() = 0;

				void onMouseButton(const boost::any message);

				void onMouseMove(const boost::any message);
		};
	}
}

#endif /* OPENGLDEMO_H_ */
