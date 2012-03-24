/*
 * Copyright © 2012 Simple Entertainment Limited
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
#include "../../math/MathFactory.h"
#include "Capsule.h"

namespace simplicity
{
	Capsule::Capsule() :
		center(MathFactory::getInstance().createTranslationVector()), colour(
			MathFactory::getInstance().createColourVector()), length(1.0f), radius(1.0f)
	{
		colour->setRed(1.0f);
		colour->setGreen(1.0f);
		colour->setBlue(1.0f);
	}

	Capsule::~Capsule()
	{
	}

	const TranslationVector<>& Capsule::getCenter() const
	{
		return *center;
	}

	ColourVector<>& Capsule::getColour() const
	{
		return *colour;
	}

	float Capsule::getLength() const
	{
		return length;
	}

	float Capsule::getRadius() const
	{
		return radius;
	}

	void Capsule::setColour(std::shared_ptr<ColourVector<> > colour)
	{
		this->colour = colour;
	}

	void Capsule::setLength(const float length)
	{
		this->length = length;
	}

	void Capsule::setRadius(const float radius)
	{
		this->radius = radius;
	}
}
