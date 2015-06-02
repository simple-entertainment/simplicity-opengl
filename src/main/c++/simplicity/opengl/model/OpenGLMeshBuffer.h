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

#include <simplicity/model/MeshBuffer.h>

#include "../common/OpenGLBuffer.h"

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
				OpenGLMeshBuffer(const unsigned int vertexCount, unsigned int indexCount,
						Buffer::AccessHint accessHint);

				~OpenGLMeshBuffer();

				Buffer::AccessHint getAccessHint() const override;

				unsigned int getBaseIndex(const Mesh& mesh) const override;

				unsigned int getBaseVertex(const Mesh& mesh) const override;

				MeshData& getData(const Mesh& mesh, bool readable) override;

				const MeshData& getData(const Mesh& mesh) const override;

				unsigned int getIndexCount(const Mesh& mesh) const override;

				PrimitiveType getPrimitiveType() const override;

				GLuint getVAOName() const;

				unsigned int getVertexCount(const Mesh& mesh) const override;

				bool isIndexed() const override;

				void releaseData(const Mesh& mesh) const override;

				void setPrimitiveType(PrimitiveType primitiveType) override;

			private:
				struct MetaData
				{
					MetaData();

					std::map<const Mesh*, unsigned int> baseIndices;

					std::map<const Mesh*, unsigned int> baseVertices;

					std::map<const Mesh*, unsigned int> indexCounts;

					unsigned int nextFreeIndex;

					unsigned int nextFreeVertex;

					std::map<const Mesh*, unsigned int> vertexCounts;

					void addMesh(const Mesh& mesh, bool indexed);

					void updateNextFree(const Mesh& mesh, bool indexed);
				};

				std::unique_ptr<OpenGLBuffer> indexBuffer;

				bool indexed;

				mutable MeshData meshData;

				mutable MetaData metaData;

				PrimitiveType primitiveType;

				GLuint vaoName;

				std::unique_ptr<OpenGLBuffer> vertexBuffer;
		};
	}
}

#endif /* OPENGLMESHBUFFER_H_ */
