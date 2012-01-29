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
#ifndef SIMPLEVECTOR4TEST_H_
#define SIMPLEVECTOR4TEST_H_

#include <gtest/gtest.h>

#include <simplicity/math/SimpleTranslationVector4.h>

namespace simplicity
{
	/**
	 * <p>
	 * Unit tests for the class {@link simplicity::SimpleTranslationVector4 SimpleTranslationVector4}.
	 * </p>
	 *
	 * @author Gary Buyn
	 */
	class SimpleTranslationVector4Test : public testing::Test
	{
		protected:
			/**
			 * An instance of the class being unit tested.
			 */
			SimpleTranslationVector4<> objectUnderTest;
	};
}

#endif /* SIMPLEVECTOR4TEST_H_ */
