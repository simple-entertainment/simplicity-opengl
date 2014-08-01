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
#include <sstream>

#include <GL/glew.h>

#include "../model/OpenGLMeshBuffer.h"
#include "OpenGL.h"
#include "MultiDrawOpenGLRenderer.h"

using namespace std;

// This needs to be small enough for the transform data to fit in the GLSL block as an array.
// TODO In the future shader storage blocks (GL 4.3 / ARB_shader_storage_buffer_objects) can remove this limitation.
const unsigned int MAX_INSTANCES_PER_DRAW = 64;

namespace simplicity
{
	namespace opengl
	{
		MultiDrawOpenGLRenderer::MultiDrawOpenGLRenderer() :
				worldTransformBuffer(Buffer::DataType::SHADER_DATA, sizeof(Matrix44) * MAX_INSTANCES_PER_DRAW, nullptr,
						Buffer::AccessHint::WRITE)
		{
		}

		void MultiDrawOpenGLRenderer::draw(const MeshBuffer& buffer, const vector<int>& counts,
				const vector<GLvoid*>& baseIndexLocations, const vector<int>& baseVertices)
		{
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
		}

		void MultiDrawOpenGLRenderer::render(const MeshBuffer& buffer,
				const vector<pair<Model*, Matrix44>>& modelsAndTransforms)
		{
			const OpenGLMeshBuffer& openGLBuffer = static_cast<const OpenGLMeshBuffer&>(buffer);
			glBindVertexArray(openGLBuffer.getVAOName());
			OpenGL::checkError();

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

			draw(buffer, counts, baseIndexLocations, baseVertices);
		}
	}
}
