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

#include <simplicity/rendering/Texture.h>

namespace simplicity
{
	namespace opengl
	{
		class OpenGLTexture : public Texture
		{
			public:
				OpenGLTexture(const unsigned char* data, unsigned int width, unsigned int height);

				OpenGLTexture(const std::string& fileName);

				~OpenGLTexture();

				void apply(Shader& shader);

				unsigned int getHeight();

				unsigned int getWidth();

				void init();

			private:
				const unsigned char* data;

				std::string fileName;

				unsigned int height;

				bool initialized;

				GLuint texture;

				unsigned int width;
		};
	}
}

#endif /* OPENGLTEXTURE_H_ */
