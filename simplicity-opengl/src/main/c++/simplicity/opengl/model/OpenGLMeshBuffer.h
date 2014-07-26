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
#ifndef OPENGLMESHBUFFER_H_
#define OPENGLMESHBUFFER_H_

#include <map>

#include <GL/glew.h>

#include <simplicity/model/MeshBuffer.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A mesh buffer implemented using OpenGL buffer objects.
		 * </p>
		 */
		class SIMPLE_API OpenGLMeshBuffer : public MeshBuffer
		{
			public:
				OpenGLMeshBuffer(const unsigned int vertexCount, unsigned int indexCount, AccessHint accessHint);

				~OpenGLMeshBuffer();

				AccessHint getAccessHint() const override;

				unsigned int getBaseIndex(const Mesh& mesh) const override;

				unsigned int getBaseVertex(const Mesh& mesh) const override;

				MeshData& getData(const Mesh& mesh, bool readable, bool writable) override;

				const MeshData& getData(const Mesh& mesh) const override;

				unsigned int getIndexCount(const Mesh& mesh) const override;

				GLuint getVAO() const;

				unsigned int getVertexCount(const Mesh& mesh) const override;

				bool isIndexed() const override;

				void releaseData(const Mesh& mesh) const override;

			private:
				AccessHint accessHint;

				mutable std::map<const Mesh*, unsigned int> baseIndices;

				mutable std::map<const Mesh*, unsigned int> baseVertices;

				GLuint ibo;

				mutable std::map<const Mesh*, unsigned int> indexCounts;

				bool indexed;

				mutable MeshData meshData;

				mutable unsigned int nextFreeIndex;

				mutable unsigned int nextFreeVertex;

				GLuint vao;

				GLuint vbo;

				mutable std::map<const Mesh*, unsigned int> vertexCounts;

				GLenum getOpenGLAccess(bool readable, bool writable) const;
		};
	}
}

#endif /* OPENGLMESHBUFFER_H_ */
