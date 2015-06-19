#ifndef OPENGLFRAMEBUFFER_H_
#define OPENGLFRAMEBUFFER_H_

#include "OpenGLTexture.h"

namespace simplicity
{
	namespace opengl
	{
		class SIMPLE_API OpenGLFrameBuffer
		{
			public:
				OpenGLFrameBuffer(std::unique_ptr<OpenGLTexture> texture);

				~OpenGLFrameBuffer();

				void apply();

				void init();

			private:
				GLuint depthBufferName;

				bool initialized;

				GLuint name;

				std::unique_ptr<OpenGLTexture> texture;
		};
	}
}

#endif /* OPENGLFRAMEBUFFER_H_ */
