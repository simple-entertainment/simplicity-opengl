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
//#include <windows.h>

#include "OpenGLLight.h"

using namespace std;

namespace simplicity
{
	namespace opengl
	{
		OpenGLLight::OpenGLLight(const string& name) :
			active(false),
			ambient(),
			attenuation(),
			diffuse(),
			direction(),
			name(name),
			range(100.0f),
			specular(),
			strength(1.0f)
		{
			activate();
		}

		void OpenGLLight::activate()
		{
			active = true;
		}

		void OpenGLLight::apply(Shader& shader, const Vector3& position)
		{
			shader.setVar(name + "Light", "attenuation", attenuation);
			shader.setVar(name + "Light", "direction", direction);
			shader.setVar(name + "Light", "position", position);
			shader.setVar(name + "Light", "range", range);
			shader.setVar(name + "Light", "specular", specular);
			shader.setVar(name + "Light", "strength", strength);

			if (active)
			{
				shader.setVar(name + "Light", "ambient", ambient);
				shader.setVar(name + "Light", "diffuse", diffuse);
				shader.setVar(name + "Light", "specular", specular);
			}
			else
			{
				shader.setVar(name + "Light", "ambient", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
				shader.setVar(name + "Light", "diffuse", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
				shader.setVar(name + "Light", "specular", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			}
		}

		void OpenGLLight::deactivate()
		{
			active = false;
		}

		const Vector4& OpenGLLight::getAmbient() const
		{
			return ambient;
		}

		const Vector3& OpenGLLight::getAttenuation() const
		{
			return attenuation;
		}

		const Vector4& OpenGLLight::getDiffuse() const
		{
			return diffuse;
		}

		const Vector3& OpenGLLight::getDirection() const
		{
			return direction;
		}

		const string& OpenGLLight::getName() const
		{
			return name;
		}

		float OpenGLLight::getRange() const
		{
			return range;
		}

		const Vector4& OpenGLLight::getSpecular() const
		{
			return specular;
		}

		float OpenGLLight::getStrength() const
		{
			return strength;
		}

		bool OpenGLLight::isActive() const
		{
			return active;
		}

		void OpenGLLight::setAmbient(const Vector4& ambient)
		{
			this->ambient = ambient;
		}

		void OpenGLLight::setAttenuation(const Vector3& attenuation)
		{
			this->attenuation = attenuation;
		}

		void OpenGLLight::setDiffuse(const Vector4& diffuse)
		{
			this->diffuse = diffuse;
		}

		void OpenGLLight::setDirection(const Vector3& direction)
		{
			this->direction = direction;
		}

		void OpenGLLight::setRange(float range)
		{
			this->range = range;
		}

		void OpenGLLight::setSpecular(const Vector4& specular)
		{
			this->specular = specular;
		}

		void OpenGLLight::setStrength(float strength)
		{
			this->strength = strength;
		}
	}
}
