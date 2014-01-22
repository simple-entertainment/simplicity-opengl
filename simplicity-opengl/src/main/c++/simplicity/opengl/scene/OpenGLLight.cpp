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

#include <GL/gl.h>

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
			strength(1.0f),
			translation()
		{
			activate();
		}

		void OpenGLLight::activate()
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			glEnable(GL_LIGHT0);

			active = true;
		}

		void OpenGLLight::apply()
		{
			if (active)
			{
				glLightfv(GL_LIGHT0, GL_POSITION, translation.getData());
				glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.getData());
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.getData());
				glLightfv(GL_LIGHT0, GL_SPECULAR, specular.getData());
			}
		}

		void OpenGLLight::deactivate()
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHT0);

			active = false;
		}

		const Vector4& OpenGLLight::getAmbientComponent() const
		{
			return ambient;
		}

		const Vector3& OpenGLLight::getAttenuation() const
		{
			return attenuation;
		}

		const Vector4& OpenGLLight::getDiffuseComponent() const
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

		const Vector4& OpenGLLight::getSpecularComponent() const
		{
			return specular;
		}

		float OpenGLLight::getStrength() const
		{
			return strength;
		}

		const Vector3& OpenGLLight::getTranslation() const
		{
			return translation;
		}

		bool OpenGLLight::isActive() const
		{
			return active;
		}

		void OpenGLLight::setAmbientComponent(const Vector4& ambient)
		{
			this->ambient = ambient;
		}

		void OpenGLLight::setAttenuation(const Vector3& attenuation)
		{
			this->attenuation = attenuation;
		}

		void OpenGLLight::setDiffuseComponent(const Vector4& diffuse)
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

		void OpenGLLight::setSpecularComponent(const Vector4& specular)
		{
			this->specular = specular;
		}

		void OpenGLLight::setStrength(float strength)
		{
			this->strength = strength;
		}

		void OpenGLLight::setTranslation(const Vector3& translation)
		{
			this->translation = translation;
		}
	}
}