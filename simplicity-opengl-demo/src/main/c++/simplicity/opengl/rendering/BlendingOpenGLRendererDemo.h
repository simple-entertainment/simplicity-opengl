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
#ifndef BLENDINGOPENGLRENDERERDEMO_H_
#define BLENDINGOPENGLRENDERERDEMO_H_

#include <simplicity/rendering/engine/RenderingEngine.h>

#include "../OpenGLDemo.h"

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A small demonstration of the {@link simplicity::opengl::BlendingOpenGLRenderer BlendingOpenGLRenderer}.
		 * </p>
		 */
		class BlendingOpenGLRendererDemo : public OpenGLDemo
		{
			public:
				BlendingOpenGLRendererDemo();

				std::string getDescription();

				std::shared_ptr<Engine> getEngine();

				std::string getTitle();

			private:
				/**
				 * <p>
				 * The rendering engine for the demo.
				 * </p>
				 */
				std::shared_ptr<simplicity::RenderingEngine> renderingEngine;

				void onDispose();

				void onInit();
		};
	}
}

#endif /* BLENDINGOPENGLRENDERERDEMO_H_ */
