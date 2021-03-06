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
#include <string.h>

#include <FreeImagePlus.h>

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
			dirty(false),
			format(format),
			height(height),
			initialized(false),
			rawData(new char[width * height * getPixelDepth(format)]),
			texture(0),
			width(width)
		{
			if (rawData != nullptr)
			{
				memcpy(this->rawData, rawData, width * height * getPixelDepth(format));
			}
		}

		OpenGLTexture::OpenGLTexture(Resource& image, PixelFormat format) :
			data(image.getData()),
			dirty(true),
			format(format),
			height(0),
			initialized(false),
			rawData(new char[width * height * getPixelDepth(format)]),
			texture(0),
			width(0)
		{
		}

		OpenGLTexture::~OpenGLTexture()
		{
			delete[] rawData;
		}

		void OpenGLTexture::apply()
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
		}

		unsigned int OpenGLTexture::getHeight() const
		{
			return height;
		}

		GLenum OpenGLTexture::getOpenGLInternalPixelFormat() const
		{
			if (format == PixelFormat::BGR || format == PixelFormat::RGB)
			{
				return GL_RGB;
			}

			if (format == PixelFormat::BGR_HDR || format == PixelFormat::RGB_HDR)
			{
				return GL_RGB16F;
			}

			if (format == PixelFormat::BGRA || format == PixelFormat::RGBA)
			{
				return GL_RGBA;
			}

			if (format == PixelFormat::BGRA_HDR || format == PixelFormat::RGBA_HDR)
			{
				return GL_RGBA16F;
			}

			return -1;
		}

		GLenum OpenGLTexture::getOpenGLPixelFormat() const
		{
			if (format == PixelFormat::BGR || format == PixelFormat::BGR_HDR)
			{
				return GL_BGR;
			}

			if (format == PixelFormat::BGRA || format == PixelFormat::BGRA_HDR)
			{
				return GL_BGRA;
			}

			if (format == PixelFormat::RGB || format == PixelFormat::RGB_HDR)
			{
				return GL_RGB;
			}

			if (format == PixelFormat::RGBA || format == PixelFormat::RGBA_HDR)
			{
				return GL_RGBA;
			}

			return -1;
		}

		PixelFormat OpenGLTexture::getPixelFormat() const
		{
			return format;
		}

		const char* OpenGLTexture::getRawData() const
		{
			if (dirty)
			{
				glBindTexture(GL_TEXTURE_2D, texture);
				OpenGL::checkError();

				glGetTexImage(GL_TEXTURE_2D, 0, getOpenGLInternalPixelFormat(), GL_UNSIGNED_BYTE, rawData);
				OpenGL::checkError();

				dirty = false;
			}

			return rawData;
		}

		GLuint OpenGLTexture::getTexture() const
		{
			return texture;
		}

		unsigned int OpenGLTexture::getWidth() const
		{
			return width;
		}

		void OpenGLTexture::init()
		{
			glGenTextures(1, &texture);
			OpenGL::checkError();

			if (!data.empty())
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
			}

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			OpenGL::checkError();
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			OpenGL::checkError();

			initialized = true;
		}

		void OpenGLTexture::setRawData(const char* rawData)
		{
			memcpy(this->rawData, rawData, width * height * getPixelDepth(format));

			glBindTexture(GL_TEXTURE_2D, texture);
			OpenGL::checkError();

			glTexImage2D(GL_TEXTURE_2D, 0, getOpenGLInternalPixelFormat(), width, height, 0, getOpenGLPixelFormat(),
					GL_UNSIGNED_BYTE, rawData);
			OpenGL::checkError();
		}
	}
}
