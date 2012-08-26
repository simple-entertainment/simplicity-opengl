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
#include <log4cpp/Category.hh>

#include <simplicity/Events.h>
#include <simplicity/Messages.h>
#include <simplicity/Simplicity.h>

#include "../../rendering/SimpleOpenGLCamera.h"
#include "SimpleOpenGLPickingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		SimpleOpenGLPickingEngine::SimpleOpenGLPickingEngine()
		{
		}

		SimpleOpenGLPickingEngine::~SimpleOpenGLPickingEngine()
		{
		}

		void SimpleOpenGLPickingEngine::addEntity(shared_ptr<Entity> entity)
		{
		}

		vector<shared_ptr<Action> > SimpleOpenGLPickingEngine::advance(vector<shared_ptr<Action> > actions)
		{
			if (picks.empty())
			{
				return actions;
			}

			if (renderingEngine.get())
			{
				if (renderingEngine->getCamera().get())
				{
					camera = renderingEngine->getCamera();
				}
			}

			picker->init();

			// For every pick.
			for (unsigned int index = 0; index < picks.size(); index++)
			{
				Messages::send(PICK_EVENT, picker->pickScene(*camera, picks.at(index)));
			}

			picker->dispose();

			picks.clear();

			return actions;
		}

		Pick SimpleOpenGLPickingEngine::convertPickCoordinatesFromViewportToSceneGraph(const float viewportWidth,
			const float viewportHeight, Pick pick) const
		{
			pick.height = pick.height / viewportHeight * (camera->getFrameWidth() * camera->getFrameAspectRatio());
			pick.width = pick.width / viewportWidth * camera->getFrameWidth();
			pick.x = pick.x / viewportWidth * camera->getFrameWidth();
			pick.y = pick.y / viewportHeight * (camera->getFrameWidth() * camera->getFrameAspectRatio());

			return pick;
		}

		void SimpleOpenGLPickingEngine::destroy()
		{
		}

		shared_ptr<Camera> SimpleOpenGLPickingEngine::getCamera() const
		{
			return camera;
		}

		shared_ptr<Picker> SimpleOpenGLPickingEngine::getPicker() const
		{
			return picker;
		}

		vector<Pick> SimpleOpenGLPickingEngine::getPicks() const
		{
			return picks;
		}

		shared_ptr<RenderingEngine> SimpleOpenGLPickingEngine::getRenderingEngine() const
		{
			return renderingEngine;
		}

		void SimpleOpenGLPickingEngine::onInit()
		{
		}

		void SimpleOpenGLPickingEngine::onReset()
		{
		}

		void SimpleOpenGLPickingEngine::pick(const float x, const float y, const float width, const float height)
		{
			Pick pick;
			pick.x = x;
			pick.y = y;
			pick.width = width;
			pick.height = height;

			SimpleOpenGLPickingEngine::pick(pick);
		}

		void SimpleOpenGLPickingEngine::pick(const Pick pick)
		{
			picks.push_back(pick);
		}

		void SimpleOpenGLPickingEngine::pickViewport(const int viewportWidth, const int viewportHeight, const int x,
			const int y, const int width, const int height)
		{
			Pick pick;
			pick.x = x;
			pick.y = y;
			pick.width = width;
			pick.height = height;

			pickViewport(viewportWidth, viewportHeight, pick);
		}

		void SimpleOpenGLPickingEngine::pickViewport(const int viewportWidth, const int viewportHeight, const Pick pick)
		{
			picks.push_back(convertPickCoordinatesFromViewportToSceneGraph(viewportWidth, viewportHeight, pick));
		}

		void SimpleOpenGLPickingEngine::removeEntity(const Entity& entity)
		{
		}

		void SimpleOpenGLPickingEngine::setCamera(shared_ptr<Camera> camera)
		{
			this->camera = camera;
		}

		void SimpleOpenGLPickingEngine::setPicker(shared_ptr<Picker> picker)
		{
			this->picker = picker;
		}

		void SimpleOpenGLPickingEngine::setRenderingEngine(shared_ptr<RenderingEngine> renderingEngine)
		{
			this->renderingEngine = renderingEngine;

			if (renderingEngine->getCamera().get())
			{
				camera = renderingEngine->getCamera();
			}
		}
	}
}
