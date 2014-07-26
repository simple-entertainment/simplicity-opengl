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

#include "../rendering/OpenGL.h"
#include "OpenGLMeshBuffer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLMeshBuffer::OpenGLMeshBuffer(const unsigned int vertexCount, unsigned int indexCount,
			AccessHint accessHint) :
				accessHint(accessHint),
				baseIndices(),
				baseVertices(),
				ibo(0),
				indexCounts(),
				indexed(indexCount > 0),
				meshData(),
				nextFreeIndex(0),
				nextFreeVertex(0),
				vao(0),
				vbo(0),
				vertexCounts()
		{
			// The configuration buffer (saves all the following state together).
			glGenVertexArrays(1, &vao);
			OpenGL::checkError();
			glBindVertexArray(vao);
			OpenGL::checkError();

			// The vertex buffer.
			glGenBuffers(1, &vbo);
			OpenGL::checkError();
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			OpenGL::checkError();
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, nullptr, GL_STATIC_DRAW);
			OpenGL::checkError();

			// A vertex format that matches the Vertex struct.
			glEnableVertexAttribArray(0);
			OpenGL::checkError();
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, 0);
			OpenGL::checkError();
			glEnableVertexAttribArray(1);
			OpenGL::checkError();
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 4));
			OpenGL::checkError();
			glEnableVertexAttribArray(2);
			OpenGL::checkError();
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 7));
			OpenGL::checkError();
			glEnableVertexAttribArray(3);
			OpenGL::checkError();
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 10));
			OpenGL::checkError();

			// The index buffer.
			if (indexed)
			{
				glGenBuffers(1, &ibo);
				OpenGL::checkError();
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				OpenGL::checkError();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, nullptr, GL_STATIC_DRAW);
				OpenGL::checkError();
			}

			// Make sure the VAO is not changed from outside code
		    glBindVertexArray(0);
		}

		OpenGLMeshBuffer::~OpenGLMeshBuffer()
		{
			glDeleteVertexArrays(1, &vao);
			OpenGL::checkError();

			glDeleteBuffers(1, &vbo);
			OpenGL::checkError();
			glDeleteBuffers(1, &ibo);
			OpenGL::checkError();
		}

		MeshBuffer::AccessHint OpenGLMeshBuffer::getAccessHint() const
		{
			return accessHint;
		}

		unsigned int OpenGLMeshBuffer::getBaseIndex(const Mesh& mesh) const
		{
			return baseIndices[&mesh];
		}

		unsigned int OpenGLMeshBuffer::getBaseVertex(const Mesh& mesh) const
		{
			return baseVertices[&mesh];
		}

		MeshData& OpenGLMeshBuffer::getData(const Mesh& mesh, bool readable, bool writable)
		{
			if (baseVertices.find(&mesh) == baseVertices.end())
			{
				baseVertices[&mesh] = nextFreeVertex;
				vertexCounts[&mesh] = 0;
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			meshData.vertexCount = vertexCounts[&mesh];
			GLvoid* vertexDataPointer = glMapBuffer(GL_ARRAY_BUFFER, getOpenGLAccess(readable, writable));
			OpenGL::checkError();
			meshData.vertexData = static_cast<Vertex*>(vertexDataPointer) + baseVertices[&mesh];

			if (indexed)
			{
				if (baseIndices.find(&mesh) == baseIndices.end())
				{
					baseIndices[&mesh] = nextFreeIndex;
					indexCounts[&mesh] = 0;
				}

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				meshData.indexCount = indexCounts[&mesh];
				GLvoid* indexDataPointer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, getOpenGLAccess(readable, writable));
				OpenGL::checkError();
				meshData.indexData = static_cast<unsigned int*>(indexDataPointer) + baseIndices[&mesh];
			}

			return meshData;
		}

		const MeshData& OpenGLMeshBuffer::getData(const Mesh& mesh) const
		{
			if (baseVertices.find(&mesh) == baseVertices.end())
			{
				baseVertices[&mesh] = nextFreeVertex;
				vertexCounts[&mesh] = 0;
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			meshData.vertexCount = vertexCounts[&mesh];
			GLvoid* vertexDataPointer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
			OpenGL::checkError();
			meshData.vertexData = static_cast<Vertex*>(vertexDataPointer) + baseVertices[&mesh];

			if (indexed)
			{
				if (baseIndices.find(&mesh) == baseIndices.end())
				{
					baseIndices[&mesh] = nextFreeIndex;
					indexCounts[&mesh] = 0;
				}

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				meshData.indexCount = indexCounts[&mesh];
				GLvoid* indexDataPointer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
				OpenGL::checkError();
				meshData.indexData = static_cast<unsigned int*>(indexDataPointer) + baseIndices[&mesh];
			}

			return meshData;
		}

		GLenum OpenGLMeshBuffer::getOpenGLAccess(bool readable, bool writable) const
		{
			if (readable && !writable)
			{
				return GL_READ_ONLY;
			}
			else if (!readable && writable)
			{
				return GL_WRITE_ONLY;
			}
			else
			{
				return GL_READ_WRITE;
			}
		}

		unsigned int OpenGLMeshBuffer::getIndexCount(const Mesh& mesh) const
		{
			return indexCounts[&mesh];
		}

		GLuint OpenGLMeshBuffer::getVAO() const
		{
			return vao;
		}

		unsigned int OpenGLMeshBuffer::getVertexCount(const Mesh& mesh) const
		{
			return vertexCounts[&mesh];
		}

		bool OpenGLMeshBuffer::isIndexed() const
		{
			return indexed;
		}

		void OpenGLMeshBuffer::releaseData(const Mesh& mesh) const
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			OpenGL::checkError();
			vertexCounts[&mesh] = meshData.vertexCount;

			unsigned int verticesEnd = baseVertices[&mesh] + vertexCounts[&mesh];
			if (verticesEnd > nextFreeVertex)
			{
				nextFreeVertex = verticesEnd;
			}

			if (indexed)
			{
				glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
				OpenGL::checkError();
				indexCounts[&mesh] = meshData.indexCount;

				unsigned int indicesEnd = baseIndices[&mesh] + indexCounts[&mesh];
				if (indicesEnd > nextFreeIndex)
				{
					nextFreeIndex = indicesEnd;
				}
			}
		}
	}
}
