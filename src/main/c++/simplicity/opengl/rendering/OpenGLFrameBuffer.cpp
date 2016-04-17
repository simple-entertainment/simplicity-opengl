#include <simplicity/logging/Logs.h>

#include "../common/OpenGL.h"
#include "OpenGLFrameBuffer.h"
#include "OpenGLTexture.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLFrameBuffer::OpenGLFrameBuffer(vector<shared_ptr<Texture>> textures, bool hasDepth) :
			depthBufferName(0),
			hasDepth(hasDepth),
			initialized(false),
			name(0),
			textures(textures)
		{
		}

		void OpenGLFrameBuffer::apply()
		{
			// Initialization needs to occur after OpenGL is initialized, this might not have happened when the
			// constructor is called.
			if (!initialized)
			{
				init();
			}

			glBindFramebuffer(GL_FRAMEBUFFER, name);
			OpenGL::checkError();
			glViewport(0, 0, textures[0]->getWidth(), textures[0]->getHeight());
			OpenGL::checkError();
		}

		vector<shared_ptr<Texture>>& OpenGLFrameBuffer::getTextures()
		{
			return textures;
		}

		void OpenGLFrameBuffer::init()
		{
			glGenFramebuffers(1, &name);
			OpenGL::checkError();
			glBindFramebuffer(GL_FRAMEBUFFER, name);
			OpenGL::checkError();

			if (hasDepth)
			{
				glGenRenderbuffers(1, &depthBufferName);
				OpenGL::checkError();
				glBindRenderbuffer(GL_RENDERBUFFER, depthBufferName);
				OpenGL::checkError();
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, textures[0]->getWidth(),
									  textures[0]->getHeight());
				OpenGL::checkError();
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferName);
				OpenGL::checkError();
			}

			// Bind the textures as destinations for the colors to be written to.
			vector<GLenum> drawBuffers;
			for (unsigned int index = 0; index < textures.size(); index++)
			{
				textures[index]->apply();
				glFramebufferTexture(GL_FRAMEBUFFER,
									 GL_COLOR_ATTACHMENT0 + index,
									 static_pointer_cast<OpenGLTexture>(textures[index])->getTexture(),
									 0);
				OpenGL::checkError();

				drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
			}

			// Draw to all the textures.
			glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
			OpenGL::checkError();

			auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status == GL_FRAMEBUFFER_UNSUPPORTED)
			{
				Logs::error("simplicity::opengl", "Frame buffer unsupported");
			}
			else if (status != GL_FRAMEBUFFER_COMPLETE)
			{
				Logs::error("simplicity::opengl", "Failed to create frame buffer");
			}

			initialized = true;
		}
	}
}
