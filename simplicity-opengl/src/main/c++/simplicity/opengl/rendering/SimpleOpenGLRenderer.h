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
#ifndef SIMPLEOPENGLRENDERER_H_
#define SIMPLEOPENGLRENDERER_H_

#include <simplicity/rendering/Renderer.h>

namespace simplicity
{
	namespace opengl
	{
		class SimpleOpenGLRenderer : public Renderer
		{
			public:
				SimpleOpenGLRenderer();

				void dispose();

				Shader* getShader();

				void init();

				void render(const Box& model);

				void render(const Capsule& model);

				void render(const Circle& model);

				void render(const Cube& model);

				void render(const Cylinder& model);

				void render(const Line& model);

				void render(const Mesh& model);

				void render(const Point& model);

				void render(const Sphere& model);

				void render(const Square& model);

				void render(const Text& model);

				void render(const Torus& model);

				void render(const Triangle& model);

				void setShader(std::unique_ptr<Shader> shader);

			private:
				std::unique_ptr<Shader> shader;

				int getOpenGLDrawingMode(Model::PrimitiveType primitiveType);
		};
	}
}

#endif /* SIMPLEOPENGLRENDERER_H_ */
