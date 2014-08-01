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
#ifndef MULTIDRAWOPENGLRENDER_H_
#define MULTIDRAWOPENGLRENDER_H_

#include "../common/SimpleOpenGLBuffer.h"
#include "AbstractOpenGLRenderer.h"

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A renderer implemented using OpenGL.
		 * </p>
		 */
		class SIMPLE_API MultiDrawOpenGLRenderer : public AbstractOpenGLRenderer
		{
			public:
				MultiDrawOpenGLRenderer();

				void render(const MeshBuffer& buffer,
						const std::vector<std::pair<Model*, Matrix44>>& modelsAndTransforms) override;

			private:
				SimpleOpenGLBuffer worldTransformBuffer;

				void draw(const MeshBuffer& buffer, const std::vector<int>& counts,
						const std::vector<GLvoid*>& baseIndexLocations, const std::vector<int>& baseVertices);
		};
	}
}

#endif /* MULTIDRAWOPENGLRENDER_H_ */
