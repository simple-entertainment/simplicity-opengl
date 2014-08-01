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
				Buffer::AccessHint accessHint) :
						indexBuffer(nullptr),
						indexed(indexCount > 0),
						meshData(),
						metaData(),
						primitiveType(PrimitiveType::TRIANGLE_LIST),
						vaoName(0),
						vertexBuffer(nullptr)
		{
			// The vertex array (saves all the following state together).
			glGenVertexArrays(1, &vaoName);
			OpenGL::checkError();
			glBindVertexArray(vaoName);
			OpenGL::checkError();

			vertexBuffer.reset(new SimpleOpenGLBuffer(Buffer::DataType::VERTICES, sizeof(Vertex) * vertexCount,
					nullptr));

			// A vertex format that matches the Vertex struct.
			glEnableVertexAttribArray(0);
			OpenGL::checkError();
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			OpenGL::checkError();
			glEnableVertexAttribArray(1);
			OpenGL::checkError();
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(float) * 4));
			OpenGL::checkError();
			glEnableVertexAttribArray(2);
			OpenGL::checkError();
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(float) * 7));
			OpenGL::checkError();
			glEnableVertexAttribArray(3);
			OpenGL::checkError();
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(float) * 10));
			OpenGL::checkError();

			if (indexed)
			{
				indexBuffer.reset(new SimpleOpenGLBuffer(Buffer::DataType::INDICES, sizeof(unsigned int) * indexCount,
						nullptr));
			}

			// Unbind the vertex array.
		    glBindVertexArray(0);
			OpenGL::checkError();
		}

		OpenGLMeshBuffer::~OpenGLMeshBuffer()
		{
			glDeleteVertexArrays(1, &vaoName);
			OpenGL::checkError();
		}

		Buffer::AccessHint OpenGLMeshBuffer::getAccessHint() const
		{
			return vertexBuffer->getAccessHint();
		}

		unsigned int OpenGLMeshBuffer::getBaseIndex(const Mesh& mesh) const
		{
			return metaData.baseIndices[&mesh];
		}

		unsigned int OpenGLMeshBuffer::getBaseVertex(const Mesh& mesh) const
		{
			return metaData.baseVertices[&mesh];
		}

		MeshData& OpenGLMeshBuffer::getData(const Mesh& mesh, bool readable)
		{
			metaData.addMesh(mesh, indexed);

			byte* vertexData = vertexBuffer->getData(readable);

			meshData.vertexCount = metaData.vertexCounts[&mesh];
			meshData.vertexData = reinterpret_cast<Vertex*>(vertexData) + metaData.baseVertices[&mesh];

			if (indexed)
			{
				byte* indexData = indexBuffer->getData(readable);

				meshData.indexCount = metaData.indexCounts[&mesh];
				meshData.indexData = reinterpret_cast<unsigned int*>(indexData) + metaData.baseIndices[&mesh];
			}

			return meshData;
		}

		const MeshData& OpenGLMeshBuffer::getData(const Mesh& mesh) const
		{
			// Sorry about the const casts!!!
			// Fear not though, the MeshData object they are being given to is returned as const.

			metaData.addMesh(mesh, indexed);

			byte* vertexData = const_cast<byte*>(vertexBuffer->getData());

			meshData.vertexCount = metaData.vertexCounts[&mesh];
			meshData.vertexData = reinterpret_cast<Vertex*>(vertexData) + metaData.baseVertices[&mesh];

			if (indexed)
			{
				byte* indexData = const_cast<byte*>(indexBuffer->getData());

				meshData.indexCount = metaData.indexCounts[&mesh];
				meshData.indexData = reinterpret_cast<unsigned int*>(indexData) + metaData.baseIndices[&mesh];
			}

			return meshData;
		}

		unsigned int OpenGLMeshBuffer::getIndexCount(const Mesh& mesh) const
		{
			return metaData.indexCounts[&mesh];
		}

		MeshBuffer::PrimitiveType OpenGLMeshBuffer::getPrimitiveType() const
		{
			return primitiveType;
		}

		GLuint OpenGLMeshBuffer::getVAOName() const
		{
			return vaoName;
		}

		unsigned int OpenGLMeshBuffer::getVertexCount(const Mesh& mesh) const
		{
			return metaData.vertexCounts[&mesh];
		}

		bool OpenGLMeshBuffer::isIndexed() const
		{
			return indexed;
		}

		void OpenGLMeshBuffer::releaseData(const Mesh& mesh) const
		{
			vertexBuffer->releaseData();
			metaData.vertexCounts[&mesh] = meshData.vertexCount;

			if (indexed)
			{
				indexBuffer->releaseData();
				metaData.indexCounts[&mesh] = meshData.indexCount;
			}

			metaData.updateNextFree(mesh, indexed);
		}

		void OpenGLMeshBuffer::setPrimitiveType(PrimitiveType primitiveType)
		{
			this->primitiveType = primitiveType;
		}

		OpenGLMeshBuffer::MetaData::MetaData() :
				baseIndices(),
				baseVertices(),
				indexCounts(),
				nextFreeIndex(0),
				nextFreeVertex(0),
				vertexCounts()
		{
		}

		void OpenGLMeshBuffer::MetaData::addMesh(const Mesh& mesh, bool indexed)
		{
			if (baseVertices.find(&mesh) == baseVertices.end())
			{
				baseVertices[&mesh] = nextFreeVertex;
				vertexCounts[&mesh] = 0;
			}

			if (indexed)
			{
				if (baseIndices.find(&mesh) == baseIndices.end())
				{
					baseIndices[&mesh] = nextFreeIndex;
					indexCounts[&mesh] = 0;
				}
			}
		}

		void OpenGLMeshBuffer::MetaData::updateNextFree(const Mesh& mesh, bool indexed)
		{
			unsigned int verticesEnd = baseVertices[&mesh] + vertexCounts[&mesh];
			if (verticesEnd > nextFreeVertex)
			{
				nextFreeVertex = verticesEnd;
			}

			if (indexed)
			{
				unsigned int indicesEnd = baseIndices[&mesh] + indexCounts[&mesh];
				if (indicesEnd > nextFreeIndex)
				{
					nextFreeIndex = indicesEnd;
				}
			}
		}
	}
}
