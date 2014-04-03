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
#ifndef OPENGLRENDERER_H_
#define OPENGLRENDERER_H_

#include <simplicity/rendering/Renderer.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A renderer implemented using OpenGL.
		 * </p>
		 */
		class SIMPLE_API OpenGLRenderer : public Renderer
		{
			public:
				OpenGLRenderer();

				bool clearsColorBuffer() const;

				bool clearsDepthBuffer() const;

				bool clearsStencilBuffer() const;

				void dispose();

				const Vector4& getClearingColor() const;

				Shader* getShader();

				void init();

				bool isScissorEnabled() const;

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

				void setClearBuffers(bool clearBuffers);

				void setClearColorBuffer(bool clearColorBuffer);

				void setClearDepthBuffer(bool clearDepthBuffer);

				void setClearingColor(const Vector4& clearingColor);

				void setClearStencilBuffer(bool clearStencilBuffer);

				void setScissor(const Vector<unsigned int, 2>& topLeft, const Vector<unsigned int, 2>& bottomRight);

				void setScissorEnabled(bool scissorEnabled);

				void setShader(std::unique_ptr<Shader> shader);

			private:
				bool clearColorBuffer;

				bool clearDepthBuffer;

				Vector4 clearingColor;

				bool clearStencilBuffer;

				std::unique_ptr<Shader> shader;

				int getOpenGLDrawingMode(Model::PrimitiveType primitiveType);
		};
	}
}

#endif /* OPENGLRENDERER_H_ */
