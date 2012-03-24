/*
 * Copyright © 2012 Simple Entertainment Limited
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
#ifndef INDEXEDVERTEXGROUP_H_
#define INDEXEDVERTEXGROUP_H_

#include "VertexGroup.h"

namespace simplicity
{
	class IndexedVertexGroup : public VertexGroup
	{
		public:
			/**
			 * <p>
			 * Retrieves the indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 * </p>
			 *
			 * @return The indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 */
			virtual std::vector<int>& getIndices() = 0;

			/**
			 * <p>
			 * Retrieves the indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 * </p>
			 *
			 * @return The indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 */
			virtual const std::vector<int>& getIndices() const = 0;

			/**
			 * <p>
			 * Sets the indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 * </p>
			 *
			 * @param indices The indices of all the vertices in this <code>IndexedVertexGroup</code>.
			 */
			virtual void setIndices(std::shared_ptr<std::vector<int> > indices) = 0;
	};
}

#endif /* INDEXEDVERTEXGROUP_H_ */
