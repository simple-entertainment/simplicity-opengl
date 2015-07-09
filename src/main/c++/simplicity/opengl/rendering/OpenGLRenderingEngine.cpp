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
#include <algorithm>

#include <simplicity/Simplicity.h>

#include "../common/OpenGL.h"
#include "../model/OpenGLMeshBuffer.h"
#include "DefaultShaderSource.h"
#include "OpenGLRenderingEngine.h"
#include "OpenGLPipeline.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLRenderingEngine::OpenGLRenderingEngine() :
				frameBuffer(),
				frameBufferChanged(false)
		{
		}

		void OpenGLRenderingEngine::dispose()
		{
			// Revert blending settings.
			glBlendFunc(GL_ONE, GL_ZERO);
			OpenGL::checkError();
			glDisable(GL_BLEND);
			OpenGL::checkError();

			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			OpenGL::checkError();

			// Revert depth test settings.
			glDepthFunc(GL_LESS);
			OpenGL::checkError();
			glDisable(GL_DEPTH_TEST);
			OpenGL::checkError();

			// Revert face culling settings.
			glDisable(GL_CULL_FACE);
			OpenGL::checkError();
		}

		void OpenGLRenderingEngine::draw(const MeshBuffer& buffer, const Mesh& mesh) const
		{
			GLenum drawingMode = getOpenGLDrawingMode(buffer.getPrimitiveType());

			if (buffer.isIndexed())
			{
				glDrawElementsBaseVertex(
						drawingMode,
						buffer.getIndexCount(mesh),
						GL_UNSIGNED_INT,
						reinterpret_cast<GLvoid*>(buffer.getBaseIndex(mesh) * sizeof(unsigned int)),
						buffer.getBaseVertex(mesh));
				OpenGL::checkError();
			}
			else
			{
				glDrawArrays(
						drawingMode,
						buffer.getBaseVertex(mesh),
						buffer.getVertexCount(mesh));
				OpenGL::checkError();
			}
		}

		GLenum OpenGLRenderingEngine::getOpenGLDrawingMode(MeshBuffer::PrimitiveType primitiveType) const
		{
			if (primitiveType == MeshBuffer::PrimitiveType::POINTS)
			{
				return GL_POINTS;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::LINE_LIST)
			{
				return GL_LINE;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::LINE_STRIP)
			{
				return GL_LINE_STRIP;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::TRIANGLE_LIST)
			{
				return GL_TRIANGLES;
			}
			else if (primitiveType == MeshBuffer::PrimitiveType::TRIANGLE_STRIP)
			{
				return GL_TRIANGLE_STRIP;
			}

			return GL_TRIANGLES;
		}

		void OpenGLRenderingEngine::init()
		{
			// Ensure objects further from the viewpoint are not drawn over the top of closer objects. To assist multi
			// pass rendering, objects at the exact same distance can be rendered over (i.e. the object will be rendered
			// using the result of the last Renderer executed).
			glDepthFunc(GL_LEQUAL);
			OpenGL::checkError();
			glEnable(GL_DEPTH_TEST);
			OpenGL::checkError();

			// Only render the front (counter-clockwise) side of a polygon.
			glEnable(GL_CULL_FACE);
			OpenGL::checkError();

			// Enable blending for rendering transparency.
			glEnable(GL_BLEND);
			OpenGL::checkError();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			OpenGL::checkError();

			if (getDefaultPipeline() == nullptr)
			{
				// Provide the default pipeline.
				unique_ptr<OpenGLShader> vertexShader(
						new OpenGLShader(Shader::Type::VERTEX, defaultVertexShaderSource));
				unique_ptr<OpenGLShader> fragmentShader(
						new OpenGLShader(Shader::Type::FRAGMENT, defaultFragmentShaderSource));
				unique_ptr<Pipeline> defaultPipeline(new OpenGLPipeline(move(vertexShader), move(fragmentShader)));
				setDefaultPipeline(move(defaultPipeline));
			}
		}

		void OpenGLRenderingEngine::postAdvance()
		{
		}

		bool OpenGLRenderingEngine::preAdvance()
		{
			// If we are using FreeGLUT the window may have been closed during this frame.
			// This is a bit ugly but we need to check for it since OpenGL would no longer be available.
			if (Simplicity::getState() == Simplicity::State::STOPPING)
			{
				return false;
			}

			if (frameBufferChanged)
			{
				frameBuffer->apply();
				frameBufferChanged = false;
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			OpenGL::checkError();

			return true;
		}

		void OpenGLRenderingEngine::render(const MeshBuffer& buffer, Pipeline& pipeline,
										   const vector<pair<Model*, Matrix44>>& modelsAndTransforms) const
		{
			const OpenGLMeshBuffer& openGLBuffer = static_cast<const OpenGLMeshBuffer&>(buffer);
			glBindVertexArray(openGLBuffer.getVAOName());
			OpenGL::checkError();

			for (const pair<Model*, Matrix44>& modelAndTransform : modelsAndTransforms)
			{
				if (modelAndTransform.first->getTypeID() != Mesh::TYPE_ID)
				{
					continue;
				}

				const Mesh* mesh = static_cast<const Mesh*>(modelAndTransform.first);

				pipeline.set("worldTransform", modelAndTransform.second);

				if (mesh->getTexture() != nullptr)
				{
					mesh->getTexture()->apply();
					pipeline.set("sampler", 0);
					pipeline.set("samplerEnabled", 1);
				}

				draw(buffer, *mesh);

				pipeline.set("samplerEnabled", 0);
			}
		}

		void OpenGLRenderingEngine::setFrameBuffer(unique_ptr<OpenGLFrameBuffer> frameBuffer)
		{
			this->frameBuffer = move(frameBuffer);
			frameBufferChanged = true;
		}
	}
}
