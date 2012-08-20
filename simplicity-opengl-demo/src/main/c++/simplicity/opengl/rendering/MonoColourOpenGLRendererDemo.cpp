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
#include <simplicity/opengl/rendering/MonoColourOpenGLRenderer.h>

#include "MonoColourOpenGLRendererDemo.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		MonoColourOpenGLRendererDemo::MonoColourOpenGLRendererDemo() :
			renderingEngine()
		{
		}

		string MonoColourOpenGLRendererDemo::getDescription() const
		{
			return "You'll just have to trust me on this one (unless you check the code). All the shapes are "
				"different colours but the renderer overrides that.";
		}

		shared_ptr<Engine> MonoColourOpenGLRendererDemo::getEngine() const
		{
			return renderingEngine;
		}

		string MonoColourOpenGLRendererDemo::getTitle() const
		{
			return "MonoColourOpenGLRenderer";
		}

		void MonoColourOpenGLRendererDemo::onDispose()
		{
			renderingEngine->destroy();
			removeAllEntities();
		}

		void MonoColourOpenGLRendererDemo::onInit()
		{
			renderingEngine.reset(new SimpleOpenGLRenderingEngine);

			renderingEngine->setPreferredFrequency(100);
			renderingEngine->setViewportWidth(800);
			renderingEngine->setViewportHeight(800);

			unique_ptr<ColourVector<> > clearingColour(MathFactory::getInstance().createColourVector());
			clearingColour->setRed(0.95f);
			clearingColour->setGreen(0.95f);
			clearingColour->setBlue(0.95f);
			renderingEngine->setClearingColour(move(clearingColour));

			initScene();

			shared_ptr<Camera> camera = addCamera();
			renderingEngine->setCamera(camera);

			addLight();

			addTitle(Simplicity::getScene()->getTree().getRoot());
			addDescription(Simplicity::getScene()->getTree().getRoot());

			Simplicity::getScene()->getTree().add(getModelsRoot());
			Simplicity::getScene()->getTree().connect(Simplicity::getScene()->getTree().getRoot(), *getModelsRoot());

			addCapsule(*getModelsRoot());
			addCylinder(*getModelsRoot());
			addSphere(*getModelsRoot());
			addTorus(*getModelsRoot());

			shared_ptr<MonoColourOpenGLRenderer> renderer(new MonoColourOpenGLRenderer);

			unique_ptr<ColourVector<> > renderColour(MathFactory::getInstance().createColourVector());
			renderColour->setGreen(0.5f);
			renderColour->setBlue(0.5f);
			renderer->setColour(move(renderColour));

			renderingEngine->addRenderer(renderer);

			renderingEngine->init();
		}
	}
}
