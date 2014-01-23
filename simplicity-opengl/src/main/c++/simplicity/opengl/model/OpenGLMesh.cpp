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
		OpenGLMesh::OpenGLMesh() :
			colour(0.0f, 0.0f, 0.0f, 1.0f),
			ibo(0),
			indices(),
			initialized(false),
			position(0.0f, 0.0f),
			primitiveType(TRIANGLE_LIST),
			vao(0),
			vbo(0),
			vertices(),
			visible(true)
		{
		}

		OpenGLMesh::OpenGLMesh(const vector<unsigned int>& indices, const vector<Vertex>& vertices) :
			colour(0.0f, 0.0f, 0.0f, 1.0f),
			ibo(0),
			indices(indices),
			initialized(false),
			position(0.0f, 0.0f),
			primitiveType(TRIANGLE_LIST),
			vao(0),
			vbo(0),
			vertices(vertices),
			visible(true)
		{
		}

		const Vector4& OpenGLMesh::getColour() const
		{
			return colour;
		}

		vector<unsigned int>& OpenGLMesh::getIndices()
		{
			return indices;
		}

		const vector<unsigned int>& OpenGLMesh::getIndices() const
		{
			return indices;
		}

		Texture* OpenGLMesh::getNormalMap() const
		{
			return NULL;
		}

		const Vector2& OpenGLMesh::getPosition() const
		{
			return position;
		}

		Model::PrimitiveType OpenGLMesh::getPrimitiveType() const
		{
			return primitiveType;
		}

		Texture* OpenGLMesh::getTexture() const
		{
			return NULL;
		}

		unsigned int OpenGLMesh::getVAO() const
		{
			return vao;
		}

		vector<Vertex>& OpenGLMesh::getVertices()
		{
			return vertices;
		}

		const vector<Vertex>& OpenGLMesh::getVertices() const
		{
			return vertices;
		}

		void OpenGLMesh::init() const
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// TODO Slow!!!
			float vertexData[vertices.size() * 12];
			for (unsigned int index = 0; index < vertices.size(); index++)
			{
				vertexData[index * 12] = vertices[index].color.R();
				vertexData[index * 12 + 1] = vertices[index].color.G();
				vertexData[index * 12 + 2] = vertices[index].color.B();
				vertexData[index * 12 + 3] = vertices[index].color.A();
				vertexData[index * 12 + 4] = vertices[index].normal.X();
				vertexData[index * 12 + 5] = vertices[index].normal.Y();
				vertexData[index * 12 + 6] = vertices[index].normal.Z();
				vertexData[index * 12 + 7] = vertices[index].position.X();
				vertexData[index * 12 + 8] = vertices[index].position.Y();
				vertexData[index * 12 + 9] = vertices[index].position.Z();
				vertexData[index * 12 + 10] = vertices[index].texCoord.X();
				vertexData[index * 12 + 11] = vertices[index].texCoord.Y();
			}

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 4));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 7));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (const GLvoid*) (sizeof(float) * 10));

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(),
					GL_STATIC_DRAW);

			// Make sure the VAO is not changed from outside code
		    glBindVertexArray(0);
		}

		bool OpenGLMesh::isVisible() const
		{
			return visible;
		}

		void OpenGLMesh::render(Renderer& renderer) const
		{
			// Initialization needs to occur after OpenGL is initialized, this might not have happened when the
			// constructor is called.
			if (!initialized)
			{
				init();
				initialized = true;
			}

			renderer.render(*this);
		}

		void OpenGLMesh::setColour(const Vector4& colour)
		{
			this->colour = colour;
		}

		void OpenGLMesh::setNormalMap(Texture*)
		{
		}

		void OpenGLMesh::setPosition(const Vector2& position)
		{
			this->position = position;
		}

		void OpenGLMesh::setPrimitiveType(PrimitiveType)
		{
			this->primitiveType = primitiveType;
		}

		void OpenGLMesh::setTexture(Texture*)
		{
		}

		void OpenGLMesh::setVisible(bool visible)
		{
			this->visible = visible;
		}
	}
}
