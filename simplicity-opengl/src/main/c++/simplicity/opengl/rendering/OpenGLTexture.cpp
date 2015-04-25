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
#include "FreeImagePlus.h"

#include "../common/OpenGL.h"
#include "OpenGLTexture.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLTexture::OpenGLTexture(const char* data, unsigned int length, PixelFormat format) :
			data(data, length),
			format(format),
			height(0),
			initialized(false),
			rawData(nullptr),
			texture(0),
			width(0)
		{
		}

		OpenGLTexture::OpenGLTexture(const char* rawData, unsigned int width, unsigned int height, PixelFormat format) :
			data(),
			format(format),
			height(height),
			initialized(false),
			rawData(rawData),
			texture(0),
			width(width)
		{
		}

		OpenGLTexture::OpenGLTexture(Resource& image, PixelFormat format) :
			data(image.getData()),
			format(format),
			height(0),
			initialized(false),
			rawData(nullptr),
			texture(0),
			width(0)
		{
		}

		void OpenGLTexture::apply(Pipeline& pipeline)
		{
			// Initialization needs to occur after OpenGL is initialized, this might not have happened when the
			// constructor is called.
			if (!initialized)
			{
				init();
			}

			glActiveTexture(GL_TEXTURE0);
			OpenGL::checkError();
			glBindTexture(GL_TEXTURE_2D, texture);
			OpenGL::checkError();

			pipeline.set("sampler", 0); // i.e. GL_TEXTURE0
		}

		unsigned int OpenGLTexture::getHeight()
		{
			return height;
		}

		GLenum OpenGLTexture::getOpenGLInternalPixelFormat()
		{
			if (format == PixelFormat::BGR || format == PixelFormat::RGB)
			{
				return GL_RGB;
			}

			if (format == PixelFormat::BGRA || format == PixelFormat::RGBA)
			{
				return GL_RGBA;
			}

			return -1;
		}

		GLenum OpenGLTexture::getOpenGLPixelFormat()
		{
			if (format == PixelFormat::BGR)
			{
				return GL_BGR;
			}

			if (format == PixelFormat::BGRA)
			{
				return GL_BGRA;
			}

			if (format == PixelFormat::RGB)
			{
				return GL_RGB;
			}

			if (format == PixelFormat::RGBA)
			{
				return GL_RGBA;
			}

			return -1;
		}

		unsigned int OpenGLTexture::getWidth()
		{
			return width;
		}

		void OpenGLTexture::init()
		{
			glGenTextures(1, &texture);
			OpenGL::checkError();

			if (rawData == nullptr)
			{
				glBindTexture(GL_TEXTURE_2D, texture);
				OpenGL::checkError();

				fipImage image;

				fipMemoryIO memory(reinterpret_cast<BYTE*>(&data[0]), data.size());
				image.loadFromMemory(memory);

				height = image.getHeight();
				width = image.getWidth();

				glTexImage2D(GL_TEXTURE_2D, 0, getOpenGLInternalPixelFormat(), width, height, 0,
						getOpenGLPixelFormat(), GL_UNSIGNED_BYTE, image.accessPixels());
				OpenGL::checkError();

				data.resize(0);
			}
			else
			{
				setRawData(rawData);

				// libRocket doesn't like this... TODO
				//delete rawData;
				//rawData = nullptr;
			}

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			OpenGL::checkError();
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			OpenGL::checkError();

			initialized = true;
		}

		void OpenGLTexture::setRawData(const char* rawData)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			OpenGL::checkError();

			glTexImage2D(GL_TEXTURE_2D, 0, getOpenGLInternalPixelFormat(), width, height, 0, getOpenGLPixelFormat(),
					GL_UNSIGNED_BYTE, rawData);
			OpenGL::checkError();
		}
	}
}
