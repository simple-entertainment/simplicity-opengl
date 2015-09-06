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
#include "OpenGLPipeline.h"
#include "OpenGLRenderingFactory.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "ShaderSource.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		shared_ptr<Pipeline> OpenGLRenderingFactory::createPipelineInternal(const string& name)
		{
			if (name == "simple")
			{
				unique_ptr<Shader> vertexShader = createShader(Shader::Type::VERTEX, "simple");
				unique_ptr<Shader> geometryShader = createShader(Shader::Type::GEOMETRY, "simple");
				unique_ptr<Shader> fragmentShader = createShader(Shader::Type::FRAGMENT, "simple");

				return createPipeline(move(vertexShader), move(geometryShader), move(fragmentShader));
			}

			return nullptr;
		}

		shared_ptr<Pipeline> OpenGLRenderingFactory::createPipelineInternal(unique_ptr<Shader> vertexShader,
																			unique_ptr<Shader> geometryShader,
																			unique_ptr<Shader> fragmentShader)
		{
			return shared_ptr<Pipeline>(new OpenGLPipeline(move(vertexShader), move(geometryShader),
														   move(fragmentShader)));
		}

		unique_ptr<Shader> OpenGLRenderingFactory::createShaderInternal(Shader::Type type, const Resource& resource)
		{
			return unique_ptr<Shader>(new OpenGLShader(type, resource));
		}

		unique_ptr<Shader> OpenGLRenderingFactory::createShaderInternal(Shader::Type type, const string& name)
		{
			if (type == Shader::Type::VERTEX)
			{
				if (name == "clip")
				{
					return unique_ptr<Shader>(new OpenGLShader(type, ShaderSource::vertexClip));
				}

				if (name == "simple")
				{
					return unique_ptr<Shader>(new OpenGLShader(type, ShaderSource::vertexSimple));
				}
			}

			if (type == Shader::Type::FRAGMENT)
			{
				if (name == "simple")
				{
					return unique_ptr<Shader>(new OpenGLShader(type, ShaderSource::fragmentSimple));
				}
			}

			return nullptr;
		}

		shared_ptr<Texture> OpenGLRenderingFactory::createTextureInternal(const char* data, unsigned int length,
																		  PixelFormat format)
		{
			return shared_ptr<Texture>(new OpenGLTexture(data, length, format));
		}

		shared_ptr<Texture> OpenGLRenderingFactory::createTextureInternal(char* rawData, unsigned int width,
																		  unsigned int height, PixelFormat format)
		{
			return shared_ptr<Texture>(new OpenGLTexture(rawData, width, height, format));
		}

		shared_ptr<Texture> OpenGLRenderingFactory::createTextureInternal(Resource& image, PixelFormat format)
		{
			return shared_ptr<Texture>(new OpenGLTexture(image, format));
		}
	}
}
