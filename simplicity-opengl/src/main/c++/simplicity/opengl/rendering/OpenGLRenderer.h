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
#ifndef OPENGLRENDERPASS_H_
#define OPENGLRENDERPASS_H_

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

				Pipeline* getDefaultPipeline();

				void init();

				bool isScissorEnabled() const;

				void render(const Model& model);

				void setClearBuffers(bool clearBuffers);

				void setClearColorBuffer(bool clearColorBuffer);

				void setClearDepthBuffer(bool clearDepthBuffer);

				void setClearingColor(const Vector4& clearingColor);

				void setClearStencilBuffer(bool clearStencilBuffer);

				void setScissor(const Vector<unsigned int, 2>& topLeft, const Vector<unsigned int, 2>& bottomRight);

				void setScissorEnabled(bool scissorEnabled);

				void setDefaultPipeline(std::unique_ptr<Pipeline> pipeline);

			private:
				bool clearColorBuffer;

				bool clearDepthBuffer;

				Vector4 clearingColor;

				bool clearStencilBuffer;

				std::unique_ptr<Pipeline> pipeline;

				int getOpenGLDrawingMode(Model::PrimitiveType primitiveType);
		};
	}
}

#endif /* OPENGLRENDERPASS_H_ */
