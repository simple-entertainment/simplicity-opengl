/*
 * Copyright © 2011 Simple Entertainment Limited
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
#ifndef OPENGLLIGHT_H_
#define OPENGLLIGHT_H_

#include <simplicity/scene/Light.h>

namespace simplicity
{
	namespace opengl
	{
		class OpenGLLight : public Light
		{
			public:
				OpenGLLight(const std::string& name);

				void activate();

				void apply(Shader& shader, const Vector3& position);

				void deactivate();

				const Vector4& getAmbientComponent() const;

				const Vector3& getAttenuation() const;

				const Vector4& getDiffuseComponent() const;

				const Vector3& getDirection() const;

				const std::string& getName() const;

				float getRange() const;

				const Vector4& getSpecularComponent() const;

				float getStrength() const;

				bool isActive() const;

				void setAmbientComponent(const Vector4& ambient);

				void setAttenuation(const Vector3& attenuation);

				void setDiffuseComponent(const Vector4& diffuse);

				void setDirection(const Vector3& direction);

				void setRange(float range);

				void setSpecularComponent(const Vector4& specular);

				void setStrength(float strength);

			private:
				bool active;

				Vector4 ambient;

				Vector3 attenuation;

				Vector4 diffuse;

				Vector3 direction;

				std::string name;

				float range;

				Vector4 specular;

				float strength;
		};
	}
}

#endif /* OPENGLLIGHT_H_ */
