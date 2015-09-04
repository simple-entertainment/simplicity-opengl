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

#include <simplicity/rendering/RenderingFactory.h>
#include <simplicity/Simplicity.h>

#include "../common/OpenGL.h"
#include "../model/OpenGLMeshBuffer.h"
#include "OpenGLRenderingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		/* TODO MULTI DRAW!

		// This needs to be small enough for the transform data to fit in the GLSL block as an array.
		// TODO SSBOs can remove this limitation.
		const unsigned int MAX_INSTANCES_PER_DRAW = 64;*/

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

			/* TODO MULTI DRAW!

			if (counts.size() == 0)
			{
				return;
			}

			if (buffer.isIndexed())
			{
				glMultiDrawElementsBaseVertex(
						getOpenGLDrawingMode(buffer.getPrimitiveType()),
						counts.data(),
						GL_UNSIGNED_INT,
						baseIndexLocations.data(),
						counts.size(),
						baseVertices.data());
				OpenGL::checkError();
			}
			else
			{
				glMultiDrawArrays(
						getOpenGLDrawingMode(buffer.getPrimitiveType()),
						baseVertices.data(),
						counts.data(),
						counts.size());
				OpenGL::checkError();
			}

			glFlush();
			glFinish();
			//fence = unique_ptr<OpenGLFence>(new OpenGLFence);
			//ence->wait();
			//fence = nullptr;*/
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

		void OpenGLRenderingEngine::glewInit()
		{
			glewExperimental = GL_TRUE;
			::glewInit();

			// Sometimes glewInit() gives false negatives. Lets clear the OpenGL error so it doesn't confuse us
			// elsewhere.
			glGetError();
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
				shared_ptr<Pipeline> defaultPipeline = RenderingFactory::getInstance()->createPipeline();
				setDefaultPipeline(defaultPipeline);
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

		void OpenGLRenderingEngine::render(const RenderList& renderList)
		{
			OpenGLMeshBuffer* openGLBuffer = static_cast<OpenGLMeshBuffer*>(renderList.buffer);
			glBindVertexArray(openGLBuffer->getVAOName());
			OpenGL::checkError();

			for (const pair<Model*, Matrix44>& modelAndTransform : renderList.list)
			{
				if (modelAndTransform.first->getTypeID() != Mesh::TYPE_ID)
				{
					continue;
				}

				const Mesh* mesh = static_cast<const Mesh*>(modelAndTransform.first);

				renderList.pipeline->set("worldTransform", modelAndTransform.second);

				if (mesh->getTexture() != nullptr)
				{
					mesh->getTexture()->apply();
					renderList.pipeline->set("sampler", 0);
					renderList.pipeline->set("samplerEnabled", 1);
				}

				draw(*renderList.buffer, *mesh);

				renderList.pipeline->set("samplerEnabled", 0);
			}

			/* TODO MULTI DRAW!

			vector<int> counts;
			counts.reserve(modelsAndTransforms.size());
			vector<GLvoid*> baseIndexLocations;
			baseIndexLocations.reserve(modelsAndTransforms.size());
			vector<int> baseVertices;
			baseVertices.reserve(modelsAndTransforms.size());

			getDefaultPipeline()->set("worldTransformBlock", worldTransformBuffer);
			Matrix44* worldTransforms = reinterpret_cast<Matrix44*>(worldTransformBuffer.getData(false));

			for (const pair<Model*, Matrix44>& modelAndTransform : modelsAndTransforms)
			{
				if (modelAndTransform.first->getTypeID() != Mesh::TYPE_ID)
				{
					continue;
				}

				const Mesh* mesh = static_cast<const Mesh*>(modelAndTransform.first);
				worldTransforms[counts.size()] = modelAndTransform.second;

				if (buffer.isIndexed())
				{
					counts.push_back(buffer.getIndexCount(*mesh));
					baseIndexLocations.push_back(
							reinterpret_cast<GLvoid*>(buffer.getBaseIndex(*mesh) * sizeof(unsigned int)));
				}
				else
				{
					counts.push_back(buffer.getVertexCount(*mesh));
				}

				baseVertices.push_back(buffer.getBaseVertex(*mesh));

				if (counts.size() == MAX_INSTANCES_PER_DRAW)
				{
					worldTransformBuffer.releaseData();

					draw(buffer, counts, baseIndexLocations, baseVertices);
					counts.clear();
					baseIndexLocations.clear();
					baseVertices.clear();

					worldTransforms = reinterpret_cast<Matrix44*>(worldTransformBuffer.getData(false));
				}
			}

			worldTransformBuffer.releaseData();

			draw(buffer, counts, baseIndexLocations, baseVertices);*/
		}

		void OpenGLRenderingEngine::setFrameBuffer(unique_ptr<OpenGLFrameBuffer> frameBuffer)
		{
			this->frameBuffer = move(frameBuffer);
			frameBufferChanged = true;
		}
	}
}
