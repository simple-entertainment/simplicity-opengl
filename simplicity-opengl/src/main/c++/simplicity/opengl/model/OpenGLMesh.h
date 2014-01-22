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
		class OpenGLMesh : public Mesh
		{
			public:
				OpenGLMesh();

				OpenGLMesh(const std::vector<int>& indices, const std::vector<Vertex>& vertices);

				const Vector4& getColour() const;

				unsigned int getID() const;

				std::vector<int>& getIndices();

				const std::vector<int>& getIndices() const;

				Texture* getNormalMap() const;

				const Vector2& getPosition() const;

				PrimitiveType getPrimitiveType() const;

				Texture* getTexture() const;

				std::vector<Vertex>& getVertices();

				const std::vector<Vertex>& getVertices() const;

				bool isVisible() const;

				void render(Renderer& renderer) const;

				void setColour(const Vector4& colour);

				void setNormalMap(Texture* texture);

				void setPosition(const Vector2& position);

				void setPrimitiveType(PrimitiveType primitiveType);

				void setTexture(Texture* texture);

				void setVisible(bool visible);

			private:
				Vector4 colour;

				std::vector<int> indices;

				mutable bool initialized;

				Vector2 position;

				PrimitiveType primitiveType;

				mutable GLuint vbo;

				std::vector<Vertex> vertices;

				bool visible;

				void init() const;
		};
	}
}

#endif /* OPENGLMESH_H_ */