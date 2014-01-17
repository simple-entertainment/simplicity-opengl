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
#ifndef OPENGLRENDERINGENGINE_H_
#define OPENGLRENDERINGENGINE_H_

#include <map>

#include <simplicity/graph/Graph.h>
#include <simplicity/rendering/RenderingEngine.h>

namespace simplicity
{
	namespace opengl
	{
		class OpenGLRenderingEngine : public RenderingEngine
		{
			public:
				OpenGLRenderingEngine();

				void addEntity(Entity& entity);

				void addLight(std::unique_ptr<Light> light);

				void addRenderer(std::unique_ptr<Renderer> renderer);

				void advance();

				void destroy();

				Camera* getCamera() const;

				const Vector4& getClearingColour() const;

				const Graph* getGraph() const;

				int getHeight() const;

				int getWidth() const;

				void init();

				void removeEntity(const Entity& entity);

				void removeRenderer(const Renderer& renderer);

				void setCamera(std::unique_ptr<Camera> camera);

				void setClearingColour(const Vector4& clearingColour);

				void setGraph(Graph* graph);

				void setHeight(int height);

				void setRendererRoot(const Renderer& renderer, const Graph& root);

				void setWidth(int width);

			private:
				std::unique_ptr<Camera> camera;

				Vector4 clearingColour;

				Graph* graph;

				int height;

				std::vector<std::unique_ptr<Light>> lights;

				std::map<const Renderer*, const Graph*> rendererRoots;

				std::vector<std::unique_ptr<Renderer>> renderers;

				int width;

				void renderGraph(Renderer& renderer, const Graph& graph);
		};
	}
}

#endif /* OPENGLRENDERINGENGINE_H_ */
