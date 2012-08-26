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
#include <algorithm>
#include <stdio.h>

#include <simplicity/common/AddressEquals.h>
#include <simplicity/graph/PreorderConstNodeIterator.h>
#include <simplicity/math/MathFactory.h>
#include <simplicity/SEInvalidOperationException.h>
#include <simplicity/Simplicity.h>

#include "SimpleOpenGLRenderingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		log4cpp::Category& SimpleOpenGLRenderingEngine::logger = log4cpp::Category::getInstance(
			"simplicity::opengl::SimpleOpenGLRenderingEngine");

		SimpleOpenGLRenderingEngine::SimpleOpenGLRenderingEngine() :
			clearingColour(MathFactory::getInstance().createColourVector()), clearsBuffers(true), initialised(false), viewportHeight(
				600), viewportWidth(800)
		{
		}

		SimpleOpenGLRenderingEngine::~SimpleOpenGLRenderingEngine()
		{
		}

		void SimpleOpenGLRenderingEngine::addEntity(std::shared_ptr<Entity> entity)
		{
		}

		void SimpleOpenGLRenderingEngine::addRenderer(const int index, std::shared_ptr<Renderer> renderer)
		{
			renderers.insert(renderers.begin() + index, renderer);

			setRendererRoot(*renderer, &Simplicity::getScene()->getTree().getRoot());
		}

		void SimpleOpenGLRenderingEngine::addRenderer(std::shared_ptr<Renderer> renderer)
		{
			addRenderer(renderers.size(), renderer);
		}

		vector<shared_ptr<Action> > SimpleOpenGLRenderingEngine::advance(vector<shared_ptr<Action> > actions)
		{
			if (!camera.get())
			{
				logger.fatal("Just how do you expect me to render without a camera then?");
				throw SEInvalidOperationException();
			}

			camera->init();

			if (!initialised)
			{
				init();
			}

			// Clear the buffers.
			if (clearsBuffers)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			}

			for (shared_ptr<Renderer> renderer : renderers)
			{
				if (rendererRoots.find(renderer.get())->second != NULL)
				{
					renderer->init();
					renderScene(*renderer);
					renderer->dispose();
				}
			}

			return actions;
		}

		void SimpleOpenGLRenderingEngine::backtrack(const int backtracks)
		{
			for (int index = 0; index < backtracks; index++)
			{
				glPopMatrix();
			}
		}

		bool SimpleOpenGLRenderingEngine::clearsBeforeRender() const
		{
			return clearsBuffers;
		}

		void SimpleOpenGLRenderingEngine::destroy()
		{
			// Revert depth test settings.
			glDepthFunc(GL_LESS);
			glDisable(GL_DEPTH_TEST);

			// Revert face culling settings.
			glDisable(GL_CULL_FACE);

			// Revert client state settings.
			glDisableClientState(GL_VERTEX_ARRAY);

			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		}

		std::shared_ptr<Camera> SimpleOpenGLRenderingEngine::getCamera() const
		{
			return camera;
		}

		const ColourVector<>& SimpleOpenGLRenderingEngine::getClearingColour() const
		{
			return *clearingColour;
		}

		TreeNode* SimpleOpenGLRenderingEngine::getRendererRoot(const Renderer& renderer) const
		{
			if (rendererRoots.find(&renderer) == rendererRoots.end())
			{
				return NULL;
			}

			return rendererRoots.find(&renderer)->second;
		}

		vector<std::shared_ptr<Renderer> > SimpleOpenGLRenderingEngine::getRenderers() const
		{
			return renderers;
		}

		int SimpleOpenGLRenderingEngine::getViewportHeight() const
		{
			return viewportHeight;
		}

		int SimpleOpenGLRenderingEngine::getViewportWidth() const
		{
			return viewportWidth;
		}

		void SimpleOpenGLRenderingEngine::onInit()
		{
			// Ensure objects further from the viewpoint are not drawn over the top of closer objects. To assist multi
			// pass rendering, objects at the exact same distance can be rendered over (i.e. the object will be rendered
			// using the result of the last Renderer executed).
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_DEPTH_TEST);

			// Only render the front (counter-clockwise) side of a polygon.
			glEnable(GL_CULL_FACE);

			// Enable model data arrays.
			glEnableClientState(GL_VERTEX_ARRAY);

			// Set the colour buffer clearing colour.
			glClearColor(clearingColour->getRed(), clearingColour->getGreen(), clearingColour->getBlue(),
				clearingColour->getAlpha());

			// Initialise the viewport size.
			glViewport(0, 0, viewportWidth, viewportHeight);

			initialised = true;
		}

		void SimpleOpenGLRenderingEngine::onReset()
		{
			init();
		}

		void SimpleOpenGLRenderingEngine::removeEntity(const Entity& entity)
		{
		}

		void SimpleOpenGLRenderingEngine::removeRenderer(const Renderer& renderer)
		{
			vector<std::shared_ptr<Renderer> >::iterator sharedRenderer = find_if(renderers.begin(), renderers.end(),
				AddressEquals<Renderer>(renderer));

			renderers.erase(remove(renderers.begin(), renderers.end(), *sharedRenderer));
			rendererRoots.erase(&renderer);
		}

		void SimpleOpenGLRenderingEngine::renderScene(Renderer& renderer)
		{
			glPushMatrix();
			{
				camera->apply();

				for (unsigned int index = 0; index < Simplicity::getScene()->getLights().size(); index++)
				{
					Simplicity::getScene()->getLights().at(index)->apply();
				}

				renderSceneGraph(renderer, *rendererRoots.find(&renderer)->second);
			}
			glPopMatrix();
		}

		void SimpleOpenGLRenderingEngine::renderSceneGraph(Renderer& renderer, const TreeNode& root)
		{
			// For every node in the traversal of the scene.
			PreorderConstNodeIterator iterator(root);
			const TreeNode* currentNode;

			while (iterator.hasMoreNodes())
			{
				// Remove transformations from the stack that do not apply to the next node.
				backtrack(iterator.getBacktracksToNextNode());

				// Apply the transformation of the current node.
				currentNode = dynamic_cast<const TreeNode*>(&iterator.getNextNode());

				glPushMatrix();

				if (currentNode == &root && currentNode != &Simplicity::getScene()->getTree().getRoot())
				{
					glMultMatrixf(currentNode->getAbsoluteTransformation()->getData().data());
				}
				else
				{
					glMultMatrixf(currentNode->getTransformation().getData().data());
				}

				// Render the current node.
				if (currentNode->getComponent() != NULL)
				{
					Model* model = dynamic_cast<Model*>(currentNode->getComponent());
					if (model != NULL)
					{
						NamedRenderer* namedRenderer = dynamic_cast<NamedRenderer*>(&renderer);
						if (namedRenderer != NULL)
						{
							namedRenderer->renderModel(*model, currentNode->getId());
						}
						else
						{
							renderer.renderModel(*model);
						}
					}
				}
			}

			// Remove all remaining transformations from the stack.
			backtrack(iterator.getBacktracksToNextNode());
		}

		void SimpleOpenGLRenderingEngine::setCamera(std::shared_ptr<Camera> camera)
		{
			this->camera = camera;
		}

		void SimpleOpenGLRenderingEngine::setClearingColour(unique_ptr<ColourVector<> > clearingColour)
		{
			this->clearingColour = move(clearingColour);

			initialised = false;
		}

		void SimpleOpenGLRenderingEngine::setClearsBeforeRender(const bool clearsBeforeRender)
		{
			clearsBuffers = clearsBeforeRender;
		}

		void SimpleOpenGLRenderingEngine::setRendererRoot(const Renderer& renderer, TreeNode* root)
		{
			rendererRoots.erase(&renderer);
			rendererRoots.insert(pair<const Renderer*, TreeNode*>(&renderer, root));
		}

		void SimpleOpenGLRenderingEngine::setViewportHeight(const int viewportHeight)
		{
			this->viewportHeight = viewportHeight;

			initialised = false;
		}

		void SimpleOpenGLRenderingEngine::setViewportWidth(const int viewportWidth)
		{
			this->viewportWidth = viewportWidth;

			initialised = false;
		}
	}
}
