/*
 * Copyright © 2011 Simple Entertainment Limited
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
#include <GL/glew.h>

#include <simplicity/model/ModelConstants.h>
#include <simplicity/model/shape/Shape.h>
#include <simplicity/Simplicity.h>

#include "SimpleOpenGLPicker.h"

using namespace simplicity::model_constants;
using namespace std;

namespace simplicity
{
	namespace opengl
	{
		SimpleOpenGLPicker::SimpleOpenGLPicker() :
			fDrawingMode(Renderer::FACES), fSelectBufferCapacity(DEFAULT_SELECT_BUFFER_CAPACITY)
		{
		}

		SimpleOpenGLPicker::~SimpleOpenGLPicker()
		{
		}

		PickEvent SimpleOpenGLPicker::createPickEvent(const int numberOfHits) const
		{
			PickEvent event;
			int bufferIndex = 0;

			for (int hitIndex = 0; hitIndex < numberOfHits; hitIndex++)
			{
				Hit hit;
				unsigned int numberOfNames = fSelectBuffer[bufferIndex++];
				hit.minimumDistance = fSelectBuffer[bufferIndex++];
				hit.maximumDistance = fSelectBuffer[bufferIndex++];

				hit.node = &Simplicity::getScene()->getTree().get(fSelectBuffer[bufferIndex]);

				Component* component = hit.node->getComponent();

				if (dynamic_cast<VertexGroup*>(component))
				{
					if (numberOfNames > 1)
					{
						hit.primitive = getSubsetVG(dynamic_cast<VertexGroup&>(*component),
							fSelectBuffer[bufferIndex + 1]);
					}
				}

				bufferIndex += numberOfNames;
				event.addHit(hit);
			}

			return (event);
		}

		void SimpleOpenGLPicker::dispose()
		{
			delete[] fSelectBuffer;
		}

		Renderer::DrawingMode SimpleOpenGLPicker::getDrawingMode() const
		{
			return (fDrawingMode);
		}

		shared_ptr<RenderingEngine> SimpleOpenGLPicker::getRenderingEngine() const
		{
			return fRenderingEngine;
		}

		unsigned int* SimpleOpenGLPicker::getSelectBuffer() const
		{
			return (fSelectBuffer);
		}

		int SimpleOpenGLPicker::getSelectBufferCapacity() const
		{
			return (fSelectBufferCapacity);
		}

		shared_ptr<VertexGroup> SimpleOpenGLPicker::getSubsetVG(VertexGroup& vertexGroup, const int index) const
		{
			shared_ptr<VertexGroup> subsetVertexGroup;

			if (fDrawingMode == Renderer::EDGES)
			{
				subsetVertexGroup = vertexGroup.createEdgeSubsetVG(index);
			}
			else if (fDrawingMode == Renderer::FACES)
			{
				subsetVertexGroup = vertexGroup.createFaceSubsetVG(index);
			}
			else if (fDrawingMode == Renderer::VERTICES)
			{
				subsetVertexGroup = vertexGroup.createVertexSubsetVG(index);
			}

			return (subsetVertexGroup);
		}

		void SimpleOpenGLPicker::init()
		{
			fSelectBuffer = new unsigned int[fSelectBufferCapacity];
			glSelectBuffer(fSelectBufferCapacity, fSelectBuffer);
		}

		PickEvent SimpleOpenGLPicker::pickScene(const Camera& camera, const Pick pick)
		{
			shared_ptr<Camera> originalCamera(fRenderingEngine->getCamera());

			fRenderingEngine->setCamera(camera.getPickCamera(pick));

			glRenderMode(GL_SELECT);

			fRenderingEngine->advance(vector<shared_ptr<Action> >());

			int numberOfHits = glRenderMode(GL_RENDER);

			fRenderingEngine->setCamera(originalCamera);

			return (createPickEvent(numberOfHits));
		}

		void SimpleOpenGLPicker::setDrawingMode(const Renderer::DrawingMode mode)
		{
			fDrawingMode = mode;
		}

		void SimpleOpenGLPicker::setRenderingEngine(shared_ptr<RenderingEngine> renderingEngine)
		{
			fRenderingEngine = renderingEngine;
		}

		void SimpleOpenGLPicker::setSelectBufferCapacity(const int selectBufferCapacity)
		{
			fSelectBufferCapacity = selectBufferCapacity;
		}
	}
}
