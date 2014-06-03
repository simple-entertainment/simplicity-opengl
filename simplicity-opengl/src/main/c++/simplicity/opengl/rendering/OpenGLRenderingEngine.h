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

#include <simplicity/model/Model.h>
#include <simplicity/rendering/RenderingEngine.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A rendering engine implemented using OpenGL.
		 * </p>
		 */
		class SIMPLE_API OpenGLRenderingEngine : public RenderingEngine
		{
			public:
				OpenGLRenderingEngine();

				void addLight(Entity& light) override;

				void addRenderer(std::unique_ptr<Renderer> renderer) override;

				void advance() override;

				Entity* getCamera() const override;

				const Graph* getGraph() const override;

				int getHeight() const override;

				int getWidth() const override;

				void onPlay() override;

				void onStop() override;

				std::unique_ptr<Renderer> removeRenderer(Renderer* renderer) override;

				void setCamera(Entity* camera) override;

				void setGraph(Graph* graph) override;

				void setHeight(int height) override;

				void setWidth(int width) override;

			private:
				struct CameraProperties
				{
					Model* bounds;
					Vector3 boundsPosition;
					Vector3 position;
					Matrix44 transform;
				};

				Entity* camera;

				Graph* graph;

				int height;

				std::vector<Entity*> lights;

				std::vector<std::unique_ptr<Renderer>> renderers;

				int width;

				CameraProperties getCameraProperties() const;

				void render(Renderer& renderer, const Entity& entity);
		};
	}
}

#endif /* OPENGLRENDERINGENGINE_H_ */
