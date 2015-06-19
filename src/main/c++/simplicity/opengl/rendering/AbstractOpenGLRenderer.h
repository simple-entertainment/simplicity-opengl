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
#ifndef ABSTRACTOPENGLRENDER_H_
#define ABSTRACTOPENGLRENDER_H_

#include <simplicity/rendering/Renderer.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A renderer that implements basic functions using OpenGL. It needs to be extended to perform the actual
		 * rendering.
		 * </p>
		 */
		class SIMPLE_API AbstractOpenGLRenderer : public Renderer
		{
			public:
				AbstractOpenGLRenderer();

				bool clearsColorBuffer() const override;

				bool clearsDepthBuffer() const override;

				bool clearsStencilBuffer() const override;

				void dispose() override;

				const Vector4& getClearingColor() const override;

				Pipeline* getDefaultPipeline() override;

				void init() override;

				bool isScissorEnabled() const override;

				void setClearBuffers(bool clearBuffers) override;

				void setClearColorBuffer(bool clearColorBuffer) override;

				void setClearDepthBuffer(bool clearDepthBuffer) override;

				void setClearingColor(const Vector4& clearingColor) override;

				void setClearStencilBuffer(bool clearStencilBuffer) override;

				void setScissor(const Vector2ui& topLeft, const Vector2ui& bottomRight) override;

				void setScissorEnabled(bool scissorEnabled) override;

				void setDefaultPipeline(std::unique_ptr<Pipeline> pipeline) override;

			protected:
				int getOpenGLDrawingMode(MeshBuffer::PrimitiveType primitiveType);

			private:
				bool clearColorBuffer;

				bool clearDepthBuffer;

				Vector4 clearingColor;

				bool clearStencilBuffer;

				std::unique_ptr<Pipeline> pipeline;
		};
	}
}

#endif /* ABSTRACTOPENGLRENDER_H_ */
