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
#include <GL/glew.h>

#include "../common/OpenGL.h"
#include "../model/OpenGLMeshBuffer.h"
#include "SimpleOpenGLRenderer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		void SimpleOpenGLRenderer::render(const MeshBuffer& buffer,
				const vector<pair<Model*, Matrix44>>& modelsAndTransforms)
		{
			const OpenGLMeshBuffer& openGLBuffer = static_cast<const OpenGLMeshBuffer&>(buffer);
			glBindVertexArray(openGLBuffer.getVAOName());
			OpenGL::checkError();

			int drawingMode = getOpenGLDrawingMode(buffer.getPrimitiveType());

			for (const pair<Model*, Matrix44>& modelAndTransform : modelsAndTransforms)
			{
				if (modelAndTransform.first->getTypeID() != Mesh::TYPE_ID)
				{
					continue;
				}

				const Mesh* mesh = static_cast<const Mesh*>(modelAndTransform.first);
				getDefaultPipeline()->set("worldTransform", modelAndTransform.second);

				if (mesh->getTexture() != nullptr)
				{
					mesh->getTexture()->apply();
					getDefaultPipeline()->set("sampler", 0);
					getDefaultPipeline()->set("samplerEnabled", 1);
				}

				if (buffer.isIndexed())
				{
					glDrawElementsBaseVertex(
							drawingMode,
							buffer.getIndexCount(*mesh),
							GL_UNSIGNED_INT,
							reinterpret_cast<GLvoid*>(buffer.getBaseIndex(*mesh) * sizeof(unsigned int)),
							buffer.getBaseVertex(*mesh));
					OpenGL::checkError();
				}
				else
				{
					glDrawArrays(
							drawingMode,
							buffer.getBaseVertex(*mesh),
							buffer.getVertexCount(*mesh));
					OpenGL::checkError();
				}

				getDefaultPipeline()->set("samplerEnabled", 0);
			}
		}
	}
}
