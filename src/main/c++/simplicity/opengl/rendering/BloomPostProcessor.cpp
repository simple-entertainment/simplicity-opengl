/*      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity. See the LICENSE file for the full license governing this code.
 */
#include <GL/glew.h>

#include <simplicity/model/ModelFactory.h>
#include <simplicity/rendering/RenderingFactory.h>
#include <simplicity/rendering/AbstractRenderingEngine.h>
#include <simplicity/resources/Resources.h>

#include "../common/OpenGL.h"
#include "BloomPostProcessor.h"
#include "OpenGLTexture.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		BloomPostProcessor::BloomPostProcessor() :
			pingFrameBuffer(RenderingFactory::createFrameBuffer(
					{
							RenderingFactory::createTexture(nullptr, 800, 600, PixelFormat::RGB_HDR)
					},
					false)),
			pongFrameBuffer(RenderingFactory::createFrameBuffer(
					{
							RenderingFactory::createTexture(nullptr, 800, 600, PixelFormat::RGB_HDR)
					},
					false)),
			quad(new Model),
			renderList()
		{
			ModelFactory::Recipe quadRecipe;
			quadRecipe.shape = ModelFactory::Recipe::Shape::RECTANGLE;
			quadRecipe.dimensions[0] = 2.0f;
			quadRecipe.dimensions[1] = 2.0f;
			std::shared_ptr<Mesh> quadMesh(ModelFactory::cookMesh(quadRecipe));
			MeshData& quadData = quadMesh->getData(true);
			quadData.vertexData[0].texCoord.Y() *= -1;
			quadData.vertexData[1].texCoord.Y() *= -1;
			quadData.vertexData[2].texCoord.Y() *= -1;
			quadData.vertexData[3].texCoord.Y() *= -1;
			quadMesh->releaseData();
			quad->setMesh(quadMesh);

			renderList.buffer = quad->getMesh()->getBuffer();
			renderList.list = { pair<Model*, Matrix44>(quad.get(), Matrix44()) };
		}

		void BloomPostProcessor::process(RenderingEngine& engine)
		{
			OpenGLRenderingEngine& openGLEngine = static_cast<OpenGLRenderingEngine&>(engine);

			shared_ptr<Pipeline> gaussianPipeline = RenderingFactory::createPipeline(
					RenderingFactory::createShader(Shader::Type::VERTEX, "clip"),
					nullptr,
					RenderingFactory::createShader(Shader::Type::FRAGMENT, *Resources::get("glsl/fragmentGaussian.glsl")));
			gaussianPipeline->apply();

			quad->getMesh()->getBuffer()->setPipeline(gaussianPipeline);
			renderList.pipeline = renderList.buffer->getPipeline();

			FrameBuffer* source = pingFrameBuffer.get();
			FrameBuffer* target = pongFrameBuffer.get();
			bool horizontal = true;
			bool first = true;
			unsigned int iterations = 5;
			for (unsigned int iteration = 0; iteration < iterations * 2; iteration++)
			{
				target->apply();
				gaussianPipeline->set("horizontal", horizontal);

				shared_ptr<Texture> sourceTexture =
						first ? engine.getFrameBuffer()->getTextures()[1] : source->getTextures()[0];

				quad->setTexture(sourceTexture);

				openGLEngine.render(renderList);

				FrameBuffer* temp = source;
				source = target;
				target = temp;

				horizontal = !horizontal;
				if (first) first = false;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			OpenGL::checkError();
			glViewport(0, 0, 800, 600);
			OpenGL::checkError();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			OpenGL::checkError();

			shared_ptr<Pipeline> blendPipeline = RenderingFactory::createPipeline(
					RenderingFactory::createShader(Shader::Type::VERTEX, "clip"),
					nullptr,
					RenderingFactory::createShader(Shader::Type::FRAGMENT, *Resources::get("glsl/fragmentBlend.glsl")));
			blendPipeline->apply();

			glActiveTexture(GL_TEXTURE1);
			OpenGL::checkError();
			glBindTexture(GL_TEXTURE_2D, static_pointer_cast<OpenGLTexture>(source->getTextures()[0])->getTexture());
			OpenGL::checkError();

			quad->getMesh()->getBuffer()->setPipeline(blendPipeline);
			quad->setTexture(engine.getFrameBuffer()->getTextures()[0]);
			renderList.pipeline = renderList.buffer->getPipeline();

			blendPipeline->set("sampler", 0);
			blendPipeline->set("bloom", 1);

			openGLEngine.render(renderList);
		}
	}
}
