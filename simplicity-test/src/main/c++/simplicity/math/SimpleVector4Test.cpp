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
#include <simplicity/math/SimpleMatrix44.h>

#include "SimpleVector4Test.h"

using namespace std;

namespace simplicity
{
	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#add() add()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, add)
	{
		objectUnderTest += SimpleVector4<>(4.0f, 2.0f, 7.5f, 3.9f);

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(5.0f, data.at(0));
		ASSERT_EQ(4.0f, data.at(1));
		ASSERT_EQ(10.5f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#crossProduct() crossProduct()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, crossProduct)
	{
		unique_ptr<Vector<> > crossProduct(objectUnderTest.crossProduct(SimpleVector4<>(3.0f, 2.0f, 1.0f, 0.0f)));

		array<float, SimpleVector4<>::SIZE>& crossProductData = crossProduct->getData();

		ASSERT_EQ(-4.0f, crossProductData.at(0));
		ASSERT_EQ(8.0f, crossProductData.at(1));
		ASSERT_EQ(-4.0f, crossProductData.at(2));
		ASSERT_EQ(1.0f, crossProductData.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::.SimpleVectorf4#dotProduct() dotProduct()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, dotProduct)
	{
		ASSERT_EQ(30.5f, objectUnderTest.dotProduct(SimpleVector4<>(4.0f, 2.0f, 7.5f, 3.9f)));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#getLength() getLength()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, getLength)
	{
		ASSERT_EQ(3.741657387f, objectUnderTest.getLength());
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#getLengthSquared() getLengthSquared()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, getLengthSquared)
	{
		ASSERT_EQ(14.0f, objectUnderTest.getLengthSquared());
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#homogenize() homogenize()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, homogenize)
	{
		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		data.at(0) = 2.0f;
		data.at(1) = 4.0f;
		data.at(2) = 6.0f;
		data.at(3) = 2.0f;

		objectUnderTest.homogenize();

		ASSERT_EQ(1.0f, data.at(0));
		ASSERT_EQ(2.0f, data.at(1));
		ASSERT_EQ(3.0f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#homogenize() homogenize()} for the special condition where
	 * the {@link simplicity::SimpleVectorf4 SimpleVectorf4} is already homogenized.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, homogenizeNotRequired)
	{
		objectUnderTest.homogenize();

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(1.0f, data.at(0));
		ASSERT_EQ(2.0f, data.at(1));
		ASSERT_EQ(3.0f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#multiply() multiply()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, multiply)
	{
		SimpleVector4<> otherVector;
		array<float, SimpleVector4<>::SIZE>& otherData = otherVector.getData();

		otherData.at(0) = 4.0f;
		otherData.at(1) = 5.0f;
		otherData.at(2) = 6.0f;
		otherData.at(3) = 1.0f;

		objectUnderTest *= otherVector;

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(4.0f, data.at(0));
		ASSERT_EQ(10.0f, data.at(1));
		ASSERT_EQ(18.0f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#multiplyWithMatrix() multiplyWithMatrix()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, multiplyWithMatrix)
	{
		SimpleMatrix44<> matrix;
		array<float, SimpleMatrix44<>::SIZE>& matrixData = matrix.getData();

		matrixData.at(0) = 1.0f;
		matrixData.at(4) = 2.0f;
		matrixData.at(8) = 3.0f;
		matrixData.at(12) = 4.0f;
		matrixData.at(1) = 2.0f;
		matrixData.at(5) = 1.0f;
		matrixData.at(9) = 4.0f;
		matrixData.at(13) = 3.0f;
		matrixData.at(2) = 3.0f;
		matrixData.at(6) = 4.0f;
		matrixData.at(10) = 1.0f;
		matrixData.at(14) = 2.0f;
		matrixData.at(3) = 0.0f;
		matrixData.at(7) = 0.0f;
		matrixData.at(11) = 0.0f;
		matrixData.at(15) = 1.0f;

		objectUnderTest *= matrix;

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(14.0f, data.at(0));
		ASSERT_EQ(16.0f, data.at(1));
		ASSERT_EQ(14.0f, data.at(2));
		ASSERT_EQ(17.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#negate() negate()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, negate)
	{
		objectUnderTest.negate();

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(-1.0f, data.at(0));
		ASSERT_EQ(-2.0f, data.at(1));
		ASSERT_EQ(-3.0f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#normalize() normalize()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, normalize)
	{
		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		data.at(0) = 0.0f;
		data.at(1) = 0.0f;
		data.at(2) = 3.0f;
		data.at(3) = 1.0f;

		objectUnderTest.normalize();

		ASSERT_EQ(0.0f, data.at(0));
		ASSERT_EQ(0.0f, data.at(1));
		ASSERT_EQ(1.0f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}

	/**
	 * <p>
	 * Unit test the method {@link simplicity::SimpleVectorf4#subtract() subtract()}.
	 * </p>
	 */
	TEST_F(SimpleVector4Test, subtract)
	{
		objectUnderTest -= SimpleVector4<>(4.0f, 2.0f, 7.5f, 3.9f);

		array<float, SimpleVector4<>::SIZE>& data = objectUnderTest.getData();

		ASSERT_EQ(-3.0f, data.at(0));
		ASSERT_EQ(0.0f, data.at(1));
		ASSERT_EQ(-4.5f, data.at(2));
		ASSERT_EQ(1.0f, data.at(3));
	}
}
