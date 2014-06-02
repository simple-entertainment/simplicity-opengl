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
#include <memory>

#include "OpenGLMesh.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLMesh::OpenGLMesh(const vector<unsigned int>& indices, const vector<Vertex>& vertices) :
			color(0.0f, 0.0f, 0.0f, 1.0f),
			ibo(0),
			indexCount(0),
			initialIndices(indices),
			initialized(false),
			initialVertices(vertices),
			primitiveType(TRIANGLE_LIST),
			vao(0),
			vbo(0),
			visible(true)
		{
		}

		const Vector4& OpenGLMesh::getColor() const
		{
			return color;
		}

		unsigned int OpenGLMesh::getIndexCount() const
		{
			if (!initialized)
			{
				return initialIndices.size();
			}

			return indexCount;
		}

		unsigned int* OpenGLMesh::getIndices()
		{
			if (!initialized)
			{
				return initialIndices.data();
			}

			// TODO
			return nullptr;
		}

		const unsigned int* OpenGLMesh::getIndices() const
		{
			if (!initialized)
			{
				return initialIndices.data();
			}

			// TODO
			return nullptr;
		}

		Texture* OpenGLMesh::getNormalMap() const
		{
			return nullptr;
		}

		Model::PrimitiveType OpenGLMesh::getPrimitiveType() const
		{
			return primitiveType;
		}

		Texture* OpenGLMesh::getTexture() const
		{
			return nullptr;
		}

		unsigned short OpenGLMesh::getTypeID() const
		{
			return TYPE_ID;
		}

		unsigned int OpenGLMesh::getVAO() const
		{
			return vao;
		}

		unsigned int OpenGLMesh::getVertexCount() const
		{
			if (!initialized)
			{
				return initialVertices.size();
			}

			// TODO
			return 0;
		}

		Vertex* OpenGLMesh::getVertices()
		{
			if (!initialized)
			{
				return initialVertices.data();
			}

			// TODO
			return nullptr;
		}

		const Vertex* OpenGLMesh::getVertices() const
		{
			if (!initialized)
			{
				return initialVertices.data();
			}

			// TODO
			return nullptr;
		}

		void OpenGLMesh::init()
		{
			if (initialized)
			{
				return;
			}

			// The configuration buffer (saves all the following state together).
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			// The vertex buffer.
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * initialVertices.size(), initialVertices.data(),
					GL_STATIC_DRAW);

			// A vertex format that matches the Vertex struct.
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 4));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 7));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 10));

			// The index buffer.
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * initialIndices.size(), initialIndices.data(),
					GL_STATIC_DRAW);

			// Make sure the VAO is not changed from outside code
		    glBindVertexArray(0);

			initialVertices.resize(0);

			indexCount = initialIndices.size();
			initialIndices.resize(0);

			initialized = true;
		}

		bool OpenGLMesh::isVisible() const
		{
			return visible;
		}

		void OpenGLMesh::resizeIndices(unsigned int size)
		{
			if (!initialized)
			{
				initialIndices.resize(size);
			}

			// TODO
		}

		void OpenGLMesh::resizeVertices(unsigned int size)
		{
			if (!initialized)
			{
				initialVertices.resize(size);
			}

			// TODO
		}

		void OpenGLMesh::setColor(const Vector4& color)
		{
			this->color = color;
		}

		void OpenGLMesh::setNormalMap(Texture* /* normalMap */)
		{
		}

		void OpenGLMesh::setPrimitiveType(PrimitiveType)
		{
			this->primitiveType = primitiveType;
		}

		void OpenGLMesh::setTexture(Texture* /* texture */)
		{
		}

		void OpenGLMesh::setVisible(bool visible)
		{
			this->visible = visible;
		}
	}
}
