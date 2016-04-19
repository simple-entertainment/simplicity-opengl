#ifndef OPENGLFRAMEBUFFER_H_
#define OPENGLFRAMEBUFFER_H_

#include <GL/glew.h>

#include <simplicity/rendering/FrameBuffer.h>

namespace simplicity
{
	namespace opengl
	{
		class SIMPLE_API OpenGLFrameBuffer : public FrameBuffer
		{
			public:
				OpenGLFrameBuffer(const std::vector<std::shared_ptr<Texture>>& textures, bool hasDepth);

				void apply() override;

				std::vector<std::shared_ptr<Texture>>& getTextures() override;

				void init();

			private:
				GLuint depthBufferName;

				bool hasDepth;

				bool initialized;

				GLuint name;

				std::vector<std::shared_ptr<Texture>> textures;
		};
	}
}

#endif /* OPENGLFRAMEBUFFER_H_ */
