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
#include <simplicity/opengl/rendering/OutlineOpenGLRenderer.h>

#include "OutlineOpenGLRendererDemo.h"

namespace simplicity
{
	namespace opengl
	{
		OutlineOpenGLRendererDemo::OutlineOpenGLRendererDemo() :
			renderingEngine()
		{
		}

		string OutlineOpenGLRendererDemo::getDescription() const
		{
			return "Renders only an outline of the shapes. Performs multiple rendering passes internally using "
				"stencilling renderers to achieve this.";
		}

		shared_ptr<Engine> OutlineOpenGLRendererDemo::getEngine() const
		{
			return renderingEngine;
		}

		string OutlineOpenGLRendererDemo::getTitle() const
		{
			return "OutlineOpenGLRenderer";
		}

		void OutlineOpenGLRendererDemo::onDispose()
		{
			renderingEngine->destroy();
			removeAllEntities();
		}

		void OutlineOpenGLRendererDemo::onInit()
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

			shared_ptr<OutlineOpenGLRenderer> renderer(new OutlineOpenGLRenderer);
			renderingEngine->addRenderer(renderer);

			renderingEngine->init();
		}
	}
}
