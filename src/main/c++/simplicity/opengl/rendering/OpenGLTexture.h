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
#ifndef OPENGLTEXTURE_H_
#define OPENGLTEXTURE_H_

#include <string>

#include <GL/glew.h>

#include <simplicity/rendering/PixelFormat.h>
#include <simplicity/rendering/Texture.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
	namespace opengl
	{
		/**
		 * <p>
		 * A texture implemented using OpenGL.
		 * </p>
		 */
		class SIMPLE_API OpenGLTexture : public Texture
		{
			public:
				/**
				 * @param data The texture data.
				 * @param length The length of the data.
				 * @param format The format of the texture.
				 */
				OpenGLTexture(const char* data, unsigned int length, PixelFormat format);

				/**
				 * @param rawData The raw texture data.
				 * @param width The width of the texture.
				 * @param height The height of the texture.
				 * @param format The format of the texture.
				 */
				OpenGLTexture(char* rawData, unsigned int width, unsigned int height, PixelFormat format);

				~OpenGLTexture();

				/**
				 * @param image The image resource.
				 * @param format The format of the texture.
				 */
				OpenGLTexture(Resource& image, PixelFormat format);

				void apply() override;

				unsigned int getHeight() const override;

				const char* getRawData() const override;

				GLuint getTexture() const;

				unsigned int getWidth() const override;

				void init() override;

				void setRawData(char* rawData) override;

			private:
				std::string data;

				PixelFormat format;

				unsigned int height;

				bool initialized;

				char* rawData;

				GLuint texture;

				unsigned int width;

				GLenum getOpenGLInternalPixelFormat() const;

				GLenum getOpenGLPixelFormat() const;
		};
	}
}

#endif /* OPENGLTEXTURE_H_ */
