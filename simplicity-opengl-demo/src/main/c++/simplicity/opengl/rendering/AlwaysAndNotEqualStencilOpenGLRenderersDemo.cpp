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
#include <boost/math/constants/constants.hpp>

#include <simplicity/graph/NodeFactory.h>
#include <simplicity/math/MathFactory.h>
#include <simplicity/Simplicity.h>

#include <simplicity/opengl/rendering/engine/SimpleOpenGLRenderingEngine.h>
#include <simplicity/opengl/rendering/AlwaysStencilOpenGLRenderer.h>
#include <simplicity/opengl/rendering/NotEqualStencilOpenGLRenderer.h>
#include <simplicity/opengl/rendering/SimpleOpenGLRenderer.h>

#include "AlwaysAndNotEqualStencilOpenGLRenderersDemo.h"

namespace simplicity
{
	namespace opengl
	{
		AlwaysAndNotEqualStencilOpenGLRenderersDemo::AlwaysAndNotEqualStencilOpenGLRenderersDemo() :
			renderingEngine()
		{
		}

		string AlwaysAndNotEqualStencilOpenGLRenderersDemo::getDescription() const
		{
			return "Pass #1 Renders the sphere, cylinder and capsule and assigns a value to the stencil buffer.\n"
				"Pass #2 Renders the torus only where the stencil buffer has not been assigned a value.\n"
				"The result of this is that the torus will never be rendered over the other shapes.";
		}

		shared_ptr<Engine> AlwaysAndNotEqualStencilOpenGLRenderersDemo::getEngine() const
		{
			return renderingEngine;
		}

		string AlwaysAndNotEqualStencilOpenGLRenderersDemo::getTitle() const
		{
			return "AlwaysStencilOpenGLRenderer and NotEqualStencilOpenGLRenderer";
		}

		void AlwaysAndNotEqualStencilOpenGLRenderersDemo::onDispose()
		{
			renderingEngine->destroy();
			removeAllEntities();
		}

		void AlwaysAndNotEqualStencilOpenGLRenderersDemo::onInit()
		{
			renderingEngine.reset(new SimpleOpenGLRenderingEngine);

			renderingEngine->setPreferredFrequency(100);
			renderingEngine->setViewportWidth(800);
			renderingEngine->setViewportHeight(800);

			unique_ptr<ColourVector<> > clearingColour = MathFactory::getInstance().createColourVector();
			clearingColour->setRed(0.95f);
			clearingColour->setGreen(0.95f);
			clearingColour->setBlue(0.95f);
			renderingEngine->setClearingColour(move(clearingColour));

			initScene();

			shared_ptr<Camera> camera = addCamera();
			renderingEngine->setCamera(camera);

			addLight();

			shared_ptr<TreeNode> textRoot = NodeFactory::getInstance().createTreeNode();
			Simplicity::getScene()->getTree().add(textRoot);
			Simplicity::getScene()->getTree().connect(Simplicity::getScene()->getTree().getRoot(), *textRoot);

			addTitle(*textRoot);
			addDescription(*textRoot);

			Simplicity::getScene()->getTree().add(getModelsRoot());
			Simplicity::getScene()->getTree().connect(Simplicity::getScene()->getTree().getRoot(), *getModelsRoot());

			shared_ptr<TreeNode> renderingPass1Root = NodeFactory::getInstance().createTreeNode();
			Simplicity::getScene()->getTree().add(renderingPass1Root);
			Simplicity::getScene()->getTree().connect(*getModelsRoot(), *renderingPass1Root);

			addCapsule(*renderingPass1Root);
			addCylinder(*renderingPass1Root);
			addSphere(*renderingPass1Root);

			shared_ptr<TreeNode> renderingPass2Root = NodeFactory::getInstance().createTreeNode();
			Simplicity::getScene()->getTree().add(renderingPass2Root);
			Simplicity::getScene()->getTree().connect(*getModelsRoot(), *renderingPass2Root);

			addTorus(*renderingPass2Root);

			shared_ptr<SimpleOpenGLRenderer> renderer(new SimpleOpenGLRenderer);

			renderingEngine->addRenderer(renderer);
			renderingEngine->setRendererRoot(*renderer, textRoot.get());

			shared_ptr<AlwaysStencilOpenGLRenderer> firstRenderer(new AlwaysStencilOpenGLRenderer(renderer));
			renderingEngine->addRenderer(firstRenderer);
			renderingEngine->setRendererRoot(*firstRenderer, renderingPass1Root.get());

			shared_ptr<NotEqualStencilOpenGLRenderer> secondRenderer(new NotEqualStencilOpenGLRenderer(renderer));
			renderingEngine->addRenderer(secondRenderer);
			renderingEngine->setRendererRoot(*secondRenderer, renderingPass2Root.get());

			renderingEngine->init();
		}
	}
}
