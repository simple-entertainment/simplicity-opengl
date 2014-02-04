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
#include <simplicity/math/Intersection.h>
#include <simplicity/math/MathFunctions.h>
#include <simplicity/scene/Camera.h>
#include <simplicity/Simplicity.h>

#include "OpenGLRenderingEngine.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLRenderingEngine::OpenGLRenderingEngine() :
			camera(),
			clearingColor(0.0f, 0.0f, 0.0f, 1.0f),
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

		void OpenGLRenderingEngine::addLight(Entity& light)
		{
			lights.push_back(&light);
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

			CameraProperties cameraProperties = getCameraProperties();

			for (unsigned int index = 0; index < renderers.size(); index++)
			{
				Renderer& renderer = *renderers[index];
				renderer.init();

				renderer.getShader()->apply();
				renderer.getShader()->setVar("cameraPosition", cameraProperties.position);
				renderer.getShader()->setVar("cameraTransform", cameraProperties.transform);

				for (unsigned int index = 0; index < lights.size(); index++)
				{
					lights[index]->getComponent<Light>()->apply(*renderer.getShader(),
							getPosition3(lights[index]->getTransform()));
				}

				if (graph == NULL)
				{
					for (Entity* entity : Simplicity::getEntities())
					{
						render(renderer, *entity);
					}
				}
				else if (cameraProperties.bounds == NULL)
				{
					render(renderer, *rendererRoots[&renderer]);
				}
				else
				{
					vector<Entity*> entities =
							rendererRoots[&renderer]->getEntitiesWithinBounds(*cameraProperties.bounds,
									cameraProperties.boundsPosition);
					for (Entity* entity : entities)
					{
						render(renderer, *entity);
					}
				}

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
			return camera;
		}

		OpenGLRenderingEngine::CameraProperties OpenGLRenderingEngine::getCameraProperties() const
		{
			CameraProperties properties;
			properties.bounds = NULL;

			if (camera == NULL)
			{
				properties.position = Vector3(0.0f, 0.0f, 0.0f);
				properties.transform.setIdentity();
			}
			else
			{
				properties.bounds = camera->getComponent<Model>(Categories::BOUNDS);
				if (properties.bounds != NULL)
				{
					properties.boundsPosition = getPosition3(camera->getTransform() *
							properties.bounds->getTransform());
				}

				Camera* cameraComponent = camera->getComponent<Camera>();
				if (cameraComponent == NULL)
				{
					properties.transform.setIdentity();
				}

				Matrix44 view = camera->getTransform() * cameraComponent->getTransform();
				properties.position = getPosition3(view);
				view.invert();

				Matrix44 projection = cameraComponent->getProjection();

				properties.transform = projection * view;
			}

			return properties;
		}

		const Vector4& OpenGLRenderingEngine::getClearingColor() const
		{
			return clearingColor;
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

			// Set the color buffer clearing color.
			glClearColor(clearingColor.X(), clearingColor.Y(), clearingColor.Z(), clearingColor.W());
		}

		void OpenGLRenderingEngine::removeEntity(const Entity& entity)
		{
		}

		void OpenGLRenderingEngine::removeRenderer(const Renderer& renderer)
		{
			renderers.erase(remove_if(renderers.begin(), renderers.end(), AddressEquals<Renderer>(renderer)));
			rendererRoots.erase(&renderer);
		}

		void OpenGLRenderingEngine::render(Renderer& renderer, const Entity& entity)
		{
			for (Model* model : entity.getComponents<Model>(Categories::RENDER))
			{
				renderer.getShader()->setVar("worldTransform", entity.getTransform() * model->getTransform());

				model->render(renderer);
			}
		}

		void OpenGLRenderingEngine::render(Renderer& renderer, const Graph& graph)
		{
			for (Entity* entity : graph.getEntities())
			{
				render(renderer, *entity);
			}

			for (unsigned int index = 0; index < graph.getChildren().size(); index++)
			{
				render(renderer, *graph.getChildren()[index]);
			}
		}

		void OpenGLRenderingEngine::setCamera(Entity* camera)
		{
			this->camera = camera;
		}

		void OpenGLRenderingEngine::setClearingColor(const Vector4& clearingColor)
		{
			this->clearingColor = clearingColor;
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
