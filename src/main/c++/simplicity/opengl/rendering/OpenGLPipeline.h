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
#ifndef OPENGLPIPELINE_H_
#define OPENGLPIPELINE_H_

#include <memory>

#include <GL/glew.h>

#include <simplicity/rendering/Pipeline.h>
#include <simplicity/rendering/Shader.h>

namespace simplicity
{
	namespace opengl
	{
		class SIMPLE_API OpenGLPipeline : public Pipeline
		{
			public:
				OpenGLPipeline(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> geometryShader,
						std::unique_ptr<Shader> fragmentShader);

				~OpenGLPipeline();

				void apply() override;

				void set(const std::string& name, const Buffer& value) override;

				void set(const std::string& name, float value) override;

				void set(const std::string& name, int value) override;

				void set(const std::string& name, const Matrix44& value) override;

				void set(const std::string& name, const Vector2& value) override;

				void set(const std::string& name, const Vector3& value) override;

				void set(const std::string& name, const Vector4& value) override;

				void set(const std::string& structName, const std::string& name, float value) override;

				void set(const std::string& structName, const std::string& name, int value) override;

				void set(const std::string& structName, const std::string& name, const Matrix44& value) override;

				void set(const std::string& structName, const std::string& name, const Vector2& value) override;

				void set(const std::string& structName, const std::string& name, const Vector3& value) override;

				void set(const std::string& structName, const std::string& name, const Vector4& value) override;

			private:
				std::unique_ptr<Shader> fragmentShader;

				std::unique_ptr<Shader> geometryShader;

				bool initialized;

				GLuint program;

				std::unique_ptr<Shader> vertexShader;

				void init();
		};
	}
}

#endif /* OPENGLPIPELINE_H_ */
