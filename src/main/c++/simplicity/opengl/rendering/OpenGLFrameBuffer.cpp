#include <simplicity/logging/Logs.h>

#include "../common/OpenGL.h"
#include "OpenGLFrameBuffer.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLFrameBuffer::OpenGLFrameBuffer(unique_ptr<OpenGLTexture> texture) :
				depthBufferName(0),
				initialized(false),
				name(0),
				texture(move(texture))
		{
		}

		OpenGLFrameBuffer::~OpenGLFrameBuffer()
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
			glViewport(0, 0, texture->getWidth(), texture->getHeight());
			OpenGL::checkError();
		}

		void OpenGLFrameBuffer::init()
		{
			glGenFramebuffers(1, &name);
			OpenGL::checkError();
			glBindFramebuffer(GL_FRAMEBUFFER, name);
			OpenGL::checkError();

			// Add the depth buffer
			glGenRenderbuffers(1, &depthBufferName);
			OpenGL::checkError();
			glBindRenderbuffer(GL_RENDERBUFFER, depthBufferName);
			OpenGL::checkError();
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texture->getWidth(), texture->getHeight());
			OpenGL::checkError();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferName);
			OpenGL::checkError();

			// Bind the color buffer to the texture
			texture->apply();
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->getTexture(), 0);
			OpenGL::checkError();
			GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, drawBuffers);
			OpenGL::checkError();

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				Logs::error("simplicity::opengl", "Failed to create frame buffer");
			}

			initialized = true;
		}
	}
}
