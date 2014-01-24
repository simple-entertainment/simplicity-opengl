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

//#include <windows.h>

#include <GL/glew.h>

#include <simplicity/common/AddressEquals.h>
#include <simplicity/math/MathFunctions.h>
#include <simplicity/scene/Camera.h>

#include "OpenGLRenderingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLRenderingEngine::OpenGLRenderingEngine() :
			camera(),
			clearingColour(0.0f, 0.0f, 0.0f, 1.0f),
			graph(NULL),
			height(600),
			lights(),
			rendererRoots(),
			renderers(),
			width(800)
		{
		}

		void OpenGLRenderingEngine::addEntity(Entity&)
		{
		}

		void OpenGLRenderingEngine::addLight(unique_ptr<Light> light)
		{
			lights.push_back(move(light));
		}

		void OpenGLRenderingEngine::addRenderer(unique_ptr<Renderer> renderer)
		{
			if (graph != NULL)
			{
				rendererRoots[renderer.get()] = graph;
			}

			renderers.push_back(move(renderer));
		}

		void OpenGLRenderingEngine::advance()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			if (graph == NULL)
			{
				return;
			}

			Matrix44 cameraTransformation;
			if (camera.get() == NULL)
			{
				cameraTransformation.setIdentity();
			}
			else
			{
				Matrix44 view = camera->getTransformation();
				view.invert();

				Matrix44 projection = camera->getComponent<Camera>()->getProjection();

				cameraTransformation = projection * view;
			}

			for (unsigned int index = 0; index < renderers.size(); index++)
			{
				Renderer& renderer = *renderers[index];
				renderer.init();

				renderer.getShader()->apply();
				renderer.getShader()->setVar("cameraPosition", MathFunctions::getTranslation3(cameraTransformation));
				renderer.getShader()->setVar("cameraTransformation", cameraTransformation);

				for (unsigned int index = 0; index < lights.size(); index++)
				{
					lights[index]->apply(*renderer.getShader());
				}

				renderGraph(renderer, *rendererRoots[&renderer]);

				renderer.dispose();
			}
		}

		void OpenGLRenderingEngine::destroy()
		{
			// Revert depth test settings.
			glDepthFunc(GL_LESS);
			glDisable(GL_DEPTH_TEST);

			// Revert face culling settings.
			glDisable(GL_CULL_FACE);

			// Revert clearing settings.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		}

		Entity* OpenGLRenderingEngine::getCamera() const
		{
			return camera.get();
		}

		const Vector4& OpenGLRenderingEngine::getClearingColour() const
		{
			return clearingColour;
		}

		const Graph* OpenGLRenderingEngine::getGraph() const
		{
			return graph;
		}

		int OpenGLRenderingEngine::getHeight() const
		{
			return height;
		}

		int OpenGLRenderingEngine::getWidth() const
		{
			return width;
		}

		void OpenGLRenderingEngine::init()
		{
			// Ensure objects further from the viewpoint are not drawn over the top of closer objects. To assist multi
			// pass rendering, objects at the exact same distance can be rendered over (i.e. the object will be rendered
			// using the result of the last Renderer executed).
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_DEPTH_TEST);

			// Only render the front (counter-clockwise) side of a polygon.
			glEnable(GL_CULL_FACE);

			// Set the colour buffer clearing colour.
			glClearColor(clearingColour.X(), clearingColour.Y(), clearingColour.Z(), clearingColour.W());
		}

		void OpenGLRenderingEngine::removeEntity(const Entity& entity)
		{
		}

		void OpenGLRenderingEngine::removeRenderer(const Renderer& renderer)
		{
			renderers.erase(remove_if(renderers.begin(), renderers.end(), AddressEquals<Renderer>(renderer)));
			rendererRoots.erase(&renderer);
			delete &renderer;
		}

		void OpenGLRenderingEngine::renderGraph(Renderer& renderer, const Graph& graph)
		{
			for (Entity* entity : graph.getEntities())
			{
				renderer.getShader()->setVar("worldTransformation", entity->getTransformation());

				for (Model* model : entity->getComponents<Model>())
				{
					model->render(renderer);
				}
			}

			for (unsigned int index = 0; index < graph.getChildren().size(); index++)
			{
				renderGraph(renderer, *graph.getChildren()[index]);
			}
		}

		void OpenGLRenderingEngine::setCamera(unique_ptr<Entity> camera)
		{
			this->camera.swap(camera);
		}

		void OpenGLRenderingEngine::setClearingColour(const Vector4& clearingColour)
		{
			this->clearingColour = clearingColour;
		}

		void OpenGLRenderingEngine::setGraph(Graph* graph)
		{
			this->graph = graph;

			for (unsigned int index = 0; index < renderers.size(); index++)
			{
				if (rendererRoots.find(renderers[index].get()) == rendererRoots.end())
				{
					rendererRoots[renderers[index].get()] = graph;
				}
			}
		}

		void OpenGLRenderingEngine::setHeight(int height)
		{
			this->height = height;
		}

		void OpenGLRenderingEngine::setRendererRoot(const Renderer& renderer, const Graph& root)
		{
			rendererRoots[&renderer] = &root;
		}

		void OpenGLRenderingEngine::setWidth(int width)
		{
			this->width = width;
		}
	}
}
