/*
 * Copyright © 2014 Simple Entertainment Limited
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

#include <simplicity/logging/Logs.h>

#include "OpenGL.h"

namespace simplicity
{
	namespace opengl
	{
		namespace OpenGL
		{
			void checkError()
			{
				GLenum error = glGetError();

				if (error != GL_NO_ERROR)
				{
					Logs::error("simplicity::opengl", "OpenGL error %i: %s", error, gluErrorString(error));
				}
			}

			void createHeadlessContext()
			{
/*#ifdef SIMPLE_LINUX
				// Taken from here: http://renderingpipeline.com/2012/05/windowless-opengl/

				typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
				typedef Bool (*glXMakeContextCurrentARBProc)(Display*, GLXDrawable, GLXDrawable, GLXContext);
				static glXCreateContextAttribsARBProc glXCreateContextAttribsARB = nullptr;
				static glXMakeContextCurrentARBProc glXMakeContextCurrentARB = nullptr;

				glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((const GLubyte*) "glXCreateContextAttribsARB");
				glXMakeContextCurrentARB = (glXMakeContextCurrentARBProc) glXGetProcAddressARB((const GLubyte*) "glXMakeContextCurrent");

				// TODO nullptr checks

				Display* display = XOpenDisplay(nullptr);

				static int visualAttribs[] = { None };
				int numberOfFramebufferConfigurations = 0;
				GLXFBConfig* fbConfigs = glXChooseFBConfig(display, DefaultScreen(display), visualAttribs, &numberOfFramebufferConfigurations);

				int context_attribs[] = {
				    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
				    GLX_CONTEXT_MINOR_VERSION_ARB, 3,
				    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
				    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
				    None
				};

				GLXContext openGLContext = glXCreateContextAttribsARB(display, fbConfigs[0], 0, True, context_attribs);

				int pbufferAttribs[] = {
				    GLX_PBUFFER_WIDTH,  32,
				    GLX_PBUFFER_HEIGHT, 32,
				    None
				};

				GLXPbuffer pbuffer = glXCreatePbuffer(display, fbConfigs[0], pbufferAttribs);

				// clean up:
				XFree(fbConfigs);
				XSync(display, False);

				if (!glXMakeContextCurrent(display, pbuffer, pbuffer, openGLContext))
				{
				    // something went wrong
				}
#endif*/
			}
		}
	}
}
