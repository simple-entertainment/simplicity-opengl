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
#include <GL/glew.h>
#include <GL/glut.h>

#include <boost/math/constants/constants.hpp>

#include <simplicity/Events.h>
#include <simplicity/graph/NodeFactory.h>
#include <simplicity/graph/SimpleTree.h>
#include <simplicity/input/MouseButtonEvent.h>
#include <simplicity/input/MouseMoveEvent.h>
#include <simplicity/math/MathFactory.h>
#include <simplicity/Messages.h>
#include <simplicity/model/ModelFactory.h>
#include <simplicity/scene/SimpleScene.h>
#include <simplicity/Simplicity.h>

#include <simplicity/opengl/model/OpenGLText.h>
#include <simplicity/opengl/rendering/SimpleOpenGLCamera.h>
#include <simplicity/opengl/rendering/SimpleOpenGLLight.h>

#include "OpenGLDemo.h"

using namespace boost::math::constants;
using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLDemo::OpenGLDemo() :
			leftButtonState(Button::State::UNKNOWN_STATE), modelsRoot(NodeFactory::getInstance().createTreeNode())
		{
		}

		shared_ptr<Camera> OpenGLDemo::addCamera()
		{
			shared_ptr<SimpleOpenGLCamera> camera(new SimpleOpenGLCamera);

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			camera->setNode(node.get());

			unique_ptr<TranslationVector<> > location(MathFactory::getInstance().createTranslationVector());
			location->setZ(15.0f);
			node->getTransformation().translate(*location);

			Simplicity::getScene()->addCamera(camera);
			Simplicity::getScene()->getTree().add(node);
			Simplicity::getScene()->getTree().connect(Simplicity::getScene()->getTree().getRoot(), *node);

			return camera;
		}

		void OpenGLDemo::addCapsule(TreeNode& parent)
		{
			shared_ptr<Entity> capsule(new Entity("capsule"));

			shared_ptr<Capsule> model = ModelFactory::getInstance().createCapsule();
			capsule->addComponent(model);

			unique_ptr<ColourVector<> > colour = MathFactory::getInstance().createColourVector();
			colour->setRed(0.75f);
			model->setColour(move(colour));

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			model->setNode(node.get());
			node->setComponent(model.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setX(-3.0f);
			location->setY(3.0f);
			node->getTransformation().translate(*location);

			Simplicity::addEntity(capsule, node, parent);
			entities.push_back(*capsule);
		}

		void OpenGLDemo::addCylinder(TreeNode& parent)
		{
			shared_ptr<Entity> cylinder(new Entity("cylinder"));

			shared_ptr<Cylinder> model = ModelFactory::getInstance().createCylinder();
			cylinder->addComponent(model);

			unique_ptr<ColourVector<> > colour = MathFactory::getInstance().createColourVector();
			colour->setGreen(0.75f);
			model->setColour(move(colour));

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			model->setNode(node.get());
			node->setComponent(model.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setY(3.0f);
			node->getTransformation().translate(*location);

			Simplicity::addEntity(cylinder, node, parent);
			entities.push_back(*cylinder);
		}

		void OpenGLDemo::addDescription(TreeNode& parent)
		{
			shared_ptr<Entity> description(new Entity("description"));

			unsigned int lineNum = 0;
			string text = getDescription();
			while (text.find('\n') != string::npos)
			{
				shared_ptr<Model> descriptionLine = createDescriptionLine(parent, text.substr(0, text.find('\n')),
					lineNum);
				description->addComponent(descriptionLine);
				descriptionLine->setEntity(description);

				text = text.substr(text.find('\n') + 1);
				lineNum++;
			}

			shared_ptr<Model> descriptionLine = createDescriptionLine(parent, text, lineNum);
			description->addComponent(descriptionLine);
			descriptionLine->setEntity(description);

			Simplicity::addEntity(description);
			entities.push_back(*description);
		}

		void OpenGLDemo::addLight()
		{
			shared_ptr<SimpleOpenGLLight> light(new SimpleOpenGLLight);

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			light->setNode(node.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setZ(15.0f);
			node->getTransformation().translate(*location);

			unique_ptr<ColourVector<> > ambientLight = MathFactory::getInstance().createColourVector();
			ambientLight->setRed(0.25f);
			ambientLight->setGreen(0.25f);
			ambientLight->setBlue(0.25f);
			light->setAmbientLight(move(ambientLight));

			unique_ptr<ColourVector<> > diffuseLight = MathFactory::getInstance().createColourVector();
			diffuseLight->setRed(0.5f);
			diffuseLight->setGreen(0.5f);
			diffuseLight->setBlue(0.5f);
			light->setDiffuseLight(move(diffuseLight));

			unique_ptr<ColourVector<> > specularLight = MathFactory::getInstance().createColourVector();
			specularLight->setRed(0.5f);
			specularLight->setGreen(0.5f);
			specularLight->setBlue(0.5f);
			light->setSpecularLight(move(specularLight));

			Simplicity::getScene()->addLight(light);
			Simplicity::getScene()->getTree().add(node);
			Simplicity::getScene()->getTree().connect(Simplicity::getScene()->getTree().getRoot(), *node);
		}

		void OpenGLDemo::addSphere(TreeNode& parent)
		{
			shared_ptr<Entity> sphere(new Entity("sphere"));

			shared_ptr<Sphere> model = ModelFactory::getInstance().createSphere();
			sphere->addComponent(model);

			unique_ptr<ColourVector<> > colour = MathFactory::getInstance().createColourVector();
			colour->setBlue(0.75f);
			model->setColour(move(colour));

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			model->setNode(node.get());
			node->setComponent(model.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setX(3.0f);
			location->setY(3.0f);
			node->getTransformation().translate(*location);

			Simplicity::addEntity(sphere, node, parent);
			entities.push_back(*sphere);
		}

		void OpenGLDemo::addTitle(TreeNode& parent)
		{
			shared_ptr<Entity> title(new Entity("title"));

			shared_ptr<Text> model = ModelFactory::getInstance().createText();
			title->addComponent(model);

			dynamic_cast<OpenGLText*>(model.get())->setFont(GLUT_BITMAP_HELVETICA_18);
			model->setText(getTitle());

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			model->setNode(node.get());
			node->setComponent(model.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setX(-3.6f);
			location->setY(2.6f);
			node->getTransformation().setTranslation(*location);

			Simplicity::addEntity(title, node, parent);
			entities.push_back(*title);
		}

		Torus& OpenGLDemo::addTorus(TreeNode& parent)
		{
			shared_ptr<Entity> torus(new Entity("torus"));

			shared_ptr<Torus> model = ModelFactory::getInstance().createTorus();
			torus->addComponent(model);

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			model->setNode(node.get());
			node->setComponent(model.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setY(-2.0f);
			node->getTransformation().translate(*location);

			Simplicity::addEntity(torus, node, parent);
			entities.push_back(*torus);

			return *model;
		}

		shared_ptr<Model> OpenGLDemo::createDescriptionLine(TreeNode& parent, const string& line,
			const unsigned int lineNum)
		{
			shared_ptr<Text> descriptionLine = ModelFactory::getInstance().createText();

			unique_ptr<ColourVector<> > colour = MathFactory::getInstance().createColourVector();
			colour->setRed(1.0f);
			colour->setGreen(1.0f);
			colour->setBlue(1.0f);
			descriptionLine->setColour(move(colour));

			descriptionLine->setText(line);

			shared_ptr<TreeNode> node = NodeFactory::getInstance().createTreeNode();
			descriptionLine->setNode(node.get());
			node->setComponent(descriptionLine.get());

			unique_ptr<TranslationVector<> > location = MathFactory::getInstance().createTranslationVector();
			location->setX(-3.6f);
			location->setY(2.4f - (lineNum / 10.0f));
			node->getTransformation().setTranslation(*location);

			Simplicity::getScene()->getTree().add(node);
			Simplicity::getScene()->getTree().connect(parent, *node);

			return descriptionLine;
		}

		void OpenGLDemo::dispose()
		{
			Messages::deregisterRecipient(MOUSE_BUTTON_EVENT, bind(&OpenGLDemo::onMouseButton, this, placeholders::_1));
			Messages::deregisterRecipient(MOUSE_MOVE_EVENT, bind(&OpenGLDemo::onMouseMove, this, placeholders::_1));

			onDispose();
		}

		std::shared_ptr<TreeNode> OpenGLDemo::getModelsRoot()
		{
			return modelsRoot;
		}

		void OpenGLDemo::init()
		{
			Messages::registerRecipient(MOUSE_BUTTON_EVENT, bind(&OpenGLDemo::onMouseButton, this, placeholders::_1));
			Messages::registerRecipient(MOUSE_MOVE_EVENT, bind(&OpenGLDemo::onMouseMove, this, placeholders::_1));

			onInit();
		}

		void OpenGLDemo::initScene() const
		{
			shared_ptr<TreeNode> root = NodeFactory::getInstance().createTreeNode();
			shared_ptr<Tree<TreeNode> > tree(new SimpleTree<TreeNode>(root));
			shared_ptr<Scene> scene(new SimpleScene(tree));
			Simplicity::setScene(scene);
		}

		void OpenGLDemo::onMouseButton(const boost::any message)
		{
			const MouseButtonEvent& event = boost::any_cast<MouseButtonEvent>(message);

			if (event.button == Mouse::Button::LEFT)
			{
				leftButtonState = event.buttonState;
			}
		}

		void OpenGLDemo::onMouseMove(const boost::any message)
		{
			if (leftButtonState != Button::State::DOWN)
			{
				return;
			}

			const MouseMoveEvent& event = boost::any_cast<MouseMoveEvent>(message);

			float angleX = (mouseX - event.x) / 10.0f;
			float angleY = (event.y - mouseY) / 10.0f;
			mouseX = event.x;
			mouseY = event.y;

			if (modelsRoot.get() != NULL)
			{
				unique_ptr<TranslationVector<> > yAxis(MathFactory::getInstance().createTranslationVector());
				yAxis->setY(1.0f);
				modelsRoot->getTransformation().rotate(angleX / pi<float>(), *yAxis);

				unique_ptr<TranslationVector<> > xAxis(MathFactory::getInstance().createTranslationVector());
				xAxis->setX(1.0f);
				modelsRoot->getTransformation().rotate(angleY / pi<float>(), *xAxis);
			}
		}

		void OpenGLDemo::removeAllEntities()
		{
			for (reference_wrapper<Entity> entity : entities)
			{
				Simplicity::removeEntity(entity.get().getName());
			}
			entities.clear();
		}
	}
}

