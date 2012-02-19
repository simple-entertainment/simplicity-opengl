/*
 * Copyright © Simple Entertainment Limited 2011
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
#include <boost/math/constants/constants.hpp>

#include <simplicity/math/MathFactory.h>
#include <simplicity/scene/SceneFactory.h>

#include <simplicity/opengl/rendering/AlwaysStencilOpenGLRenderer.h>
#include <simplicity/opengl/rendering/NotEqualStencilOpenGLRenderer.h>
#include <simplicity/opengl/rendering/SimpleOpenGLRenderer.h>
#include <simplicity/opengl/rendering/StencilClearingOpenGLRenderer.h>

#include "StencilClearingOpenGLRendererDemo.h"

namespace simplicity
{
	namespace opengl
	{
		StencilClearingOpenGLRendererDemo::StencilClearingOpenGLRendererDemo()
		{
		}

		StencilClearingOpenGLRendererDemo::~StencilClearingOpenGLRendererDemo()
		{
		}

		void StencilClearingOpenGLRendererDemo::advance()
		{
			renderingEngine.advance(shared_ptr<EngineInput>());
		}

		void StencilClearingOpenGLRendererDemo::dispose()
		{
			renderingEngine.destroy();
		}

		shared_ptr<Camera> StencilClearingOpenGLRendererDemo::getCamera()
		{
			return (renderingEngine.getCamera());
		}

		string StencilClearingOpenGLRendererDemo::getDescription()
		{
			return ("Pass #1 Renders the sphere, cylinder and capsule and assigns a value to the stencil buffer.\n"
				"Before Pass #2 Clears the stencil buffer.\n"
				"Pass #2 Renders the torus only where the stencil buffer has not been assigned a value.\n"
				"The result of this is that the torus can be rendered over the other shapes.");
		}

		string StencilClearingOpenGLRendererDemo::getTitle()
		{
			return ("StencilClearingOpenGLRenderer");
		}

		void StencilClearingOpenGLRendererDemo::init()
		{
			unique_ptr<RGBAColourVector<> > clearingColour(MathFactory::getInstance().createRGBAColourVector());
			clearingColour->setRed(0.95f);
			clearingColour->setGreen(0.95f);
			clearingColour->setBlue(0.95f);
			renderingEngine.setClearingColour(move(clearingColour));

			shared_ptr<Scene> scene(SceneFactory::getInstance().createScene());
			shared_ptr<Node> sceneRoot(SceneFactory::getInstance().createNode());
			renderingEngine.setScene(scene);

			shared_ptr<Camera> camera = addStandardCamera(sceneRoot);
			scene->addCamera(camera);
			renderingEngine.setCamera(camera);

			shared_ptr<Light> light = addStandardLight(sceneRoot);
			scene->addLight(light);
			scene->addNode(sceneRoot);

			shared_ptr<Node> renderingPass1Root(SceneFactory::getInstance().createNode());
			addStandardCapsule(renderingPass1Root);
			addStandardCylinder(renderingPass1Root);
			addStandardSphere(renderingPass1Root);
			scene->addNode(renderingPass1Root);

			shared_ptr<Node> renderingPass2Root(SceneFactory::getInstance().createNode());
			addStandardTorus(renderingPass2Root);
			scene->addNode(renderingPass2Root);

			shared_ptr<SimpleOpenGLRenderer> wrappedRenderer(new SimpleOpenGLRenderer);

			shared_ptr<AlwaysStencilOpenGLRenderer> firstRenderer(new AlwaysStencilOpenGLRenderer(wrappedRenderer));
			renderingEngine.addRenderer(firstRenderer);
			renderingEngine.setRendererRoot(*firstRenderer, renderingPass1Root);

			shared_ptr<StencilClearingOpenGLRenderer> secondRenderer(
				new StencilClearingOpenGLRenderer(
					shared_ptr < NotEqualStencilOpenGLRenderer > (new NotEqualStencilOpenGLRenderer(wrappedRenderer))));
			renderingEngine.addRenderer(secondRenderer);
			renderingEngine.setRendererRoot(*secondRenderer, renderingPass2Root);

			renderingEngine.init();
		}
	}
}
