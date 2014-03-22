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
#include "ImageMagick/Magick++.h"

#include "OpenGLTexture.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLTexture::OpenGLTexture(const char* data, unsigned int length) :
			data(data, length),
			height(0),
			initialized(false),
			rawData(NULL),
			texture(0),
			width(0)
		{
		}

		OpenGLTexture::OpenGLTexture(const char* rawData, unsigned int width, unsigned int height) :
			height(height),
			initialized(false),
			rawData(rawData),
			texture(0),
			width(width)
		{
		}

		OpenGLTexture::OpenGLTexture(Resource& image) :
			data(image.getData()),
			height(0),
			initialized(false),
			rawData(NULL),
			texture(0),
			width(0)
		{
		}

		void OpenGLTexture::apply(Shader& shader)
		{
			// Initialization needs to occur after OpenGL is initialized, this might not have happened when the
			// constructor is called.
			if (!initialized)
			{
				init();
			}

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			shader.setVar("sampler", 0);
		}

		unsigned int OpenGLTexture::getHeight()
		{
			return height;
		}

		unsigned int OpenGLTexture::getWidth()
		{
			return width;
		}

		void OpenGLTexture::init()
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			if (rawData == NULL)
			{
				Magick::Blob encodedBlob(data.data(), data.size());
				Magick::Image image(encodedBlob);
				width = image.columns();
				height = image.rows();
				Magick::Blob rgbaBlob;
				image.write(&rgbaBlob, "RGBA");

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBlob.data());
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawData);
			}

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			initialized = true;
		}
	}
}
