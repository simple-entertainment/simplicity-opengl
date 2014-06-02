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
#ifndef OPENGLMESH_H_
#define OPENGLMESH_H_

#include <vector>

#include <GL/glew.h>

#include <simplicity/model/Mesh.h>
#include <simplicity/model/Vertex.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A mesh implemented using OpenGL buffer objects.
		 * </p>
		 */
		class SIMPLE_API OpenGLMesh : public Mesh
		{
			public:
				/**
				 * <p>
				 * An ID unique to the this model class.
				 * </p>
				 */
				static const unsigned int TYPE_ID = 14;

				/**
				 * @param indices The indices into the collection of vertices.
				 * @param vertices The collection of vertices.
				 */
				OpenGLMesh(const std::vector<unsigned int>& indices, const std::vector<Vertex>& vertices);

				const Vector4& getColor() const;

				unsigned int getIndexCount() const;

				unsigned int* getIndices();

				const unsigned int* getIndices() const;

				Texture* getNormalMap() const;

				PrimitiveType getPrimitiveType() const;

				Texture* getTexture() const;

				unsigned short getTypeID() const;

				/**
				 * <p>
				 * Retrieves the OpenGL Vertex Array Object used to implement this mesh.
				 * </p>
				 *
				 * @return The OpenGL Vertex Array Object.
				 */
				unsigned int getVAO() const;

				unsigned int getVertexCount() const;

				Vertex* getVertices();

				const Vertex* getVertices() const;

				void init();

				bool isVisible() const;

				void resizeIndices(unsigned int size);

				void resizeVertices(unsigned int size);

				void setColor(const Vector4& color);

				void setNormalMap(Texture* normalMap);

				void setPrimitiveType(PrimitiveType primitiveType);

				void setTexture(Texture* texture);

				void setVisible(bool visible);

			private:
				Vector4 color;

				mutable GLuint ibo;

				unsigned int indexCount;

				std::vector<unsigned int> initialIndices;

				mutable bool initialized;

				std::vector<Vertex> initialVertices;

				PrimitiveType primitiveType;

				mutable GLuint vao;

				mutable GLuint vbo;

				bool visible;
		};
	}
}

#endif /* OPENGLMESH_H_ */
