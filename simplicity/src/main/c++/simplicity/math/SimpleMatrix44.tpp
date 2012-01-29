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
#include <boost/lexical_cast.hpp>

#include "../SEInvalidOperationException.h"
#include "SimpleMatrix44.h"
#include "SimpleVector4.h"

using namespace std;

namespace simplicity
{
	template<typename Data>
	SimpleMatrix44<Data>::SimpleMatrix44() :
		data()
	{
		setIdentity();
	}

	template<typename Data>
	SimpleMatrix44<Data>::SimpleMatrix44(const array<Data, SIZE>& data) :
		data(data)
	{
	}

	template<typename Data>
	bool SimpleMatrix44<Data>::equals(const Matrix<Data, SIZE>& otherMatrix) const
	{
		return data == otherMatrix.getData();
	}

	template<typename Data>
	array<Data, SimpleMatrix44<>::SIZE>& SimpleMatrix44<Data>::getData()
	{
		return data;
	}

	template<typename Data>
	const array<Data, SimpleMatrix44<>::SIZE>& SimpleMatrix44<Data>::getData() const
	{
		return data;
	}

	template<typename Data>
	Data SimpleMatrix44<Data>::getDeterminant() const
	{
		Data determinant = data.at(0)
			* ((data.at(5) * data.at(10) * data.at(15) + data.at(6) * data.at(11) * data.at(13)
				+ data.at(7) * data.at(9) * data.at(14)) - data.at(7) * data.at(10) * data.at(13)
				- data.at(5) * data.at(11) * data.at(14) - data.at(6) * data.at(9) * data.at(15));

		determinant -= data.at(1)
			* ((data.at(4) * data.at(10) * data.at(15) + data.at(6) * data.at(11) * data.at(12)
				+ data.at(7) * data.at(8) * data.at(14)) - data.at(7) * data.at(10) * data.at(12)
				- data.at(4) * data.at(11) * data.at(14) - data.at(6) * data.at(8) * data.at(15));

		determinant += data.at(2)
			* ((data.at(4) * data.at(9) * data.at(15) + data.at(5) * data.at(11) * data.at(12)
				+ data.at(7) * data.at(8) * data.at(13)) - data.at(7) * data.at(9) * data.at(12)
				- data.at(4) * data.at(11) * data.at(13) - data.at(5) * data.at(8) * data.at(15));

		determinant -= data.at(3)
			* ((data.at(4) * data.at(9) * data.at(14) + data.at(5) * data.at(10) * data.at(12)
				+ data.at(6) * data.at(8) * data.at(13)) - data.at(6) * data.at(9) * data.at(12)
				- data.at(4) * data.at(10) * data.at(13) - data.at(5) * data.at(8) * data.at(14));

		return determinant;
	}

	template<typename Data>
	Data SimpleMatrix44<Data>::getDeterminant33(const Data d00, const Data d10, const Data d20, const Data d01,
		const Data d11, const Data d21, const Data d02, const Data d12, const Data d22) const
	{
		return d00 * (d11 * d22 - d12 * d21) - d10 * (d01 * d22 - d02 * d21) + d20 * (d01 * d12 - d02 * d11);
	}

	template<typename Data>
	void SimpleMatrix44<Data>::invert()
	{
		Data determinant = getDeterminant();

		if (determinant == 0)
		{
			throw SEInvalidOperationException();
		}

		Data invDeterminant = 1 / determinant;

		// Calculate determinants for each value in this matrix.
		Data d00 = getDeterminant33(data.at(5), data.at(6), data.at(7), data.at(9), data.at(10), data.at(11),
			data.at(13), data.at(14), data.at(15));
		Data d01 = -getDeterminant33(data.at(4), data.at(6), data.at(7), data.at(8), data.at(10), data.at(11),
			data.at(12), data.at(14), data.at(15));
		Data d02 = getDeterminant33(data.at(4), data.at(5), data.at(7), data.at(8), data.at(9), data.at(11),
			data.at(12), data.at(13), data.at(15));
		Data d03 = -getDeterminant33(data.at(4), data.at(5), data.at(6), data.at(8), data.at(9), data.at(10),
			data.at(12), data.at(13), data.at(14));

		Data d10 = -getDeterminant33(data.at(1), data.at(2), data.at(3), data.at(9), data.at(10), data.at(11),
			data.at(13), data.at(14), data.at(15));
		Data d11 = getDeterminant33(data.at(0), data.at(2), data.at(3), data.at(8), data.at(10), data.at(11),
			data.at(12), data.at(14), data.at(15));
		Data d12 = -getDeterminant33(data.at(0), data.at(1), data.at(3), data.at(8), data.at(9), data.at(11),
			data.at(12), data.at(13), data.at(15));
		Data d13 = getDeterminant33(data.at(0), data.at(1), data.at(2), data.at(8), data.at(9), data.at(10),
			data.at(12), data.at(13), data.at(14));

		Data d20 = getDeterminant33(data.at(1), data.at(2), data.at(3), data.at(5), data.at(6), data.at(7), data.at(13),
			data.at(14), data.at(15));
		Data d21 = -getDeterminant33(data.at(0), data.at(2), data.at(3), data.at(4), data.at(6), data.at(7),
			data.at(12), data.at(14), data.at(15));
		Data d22 = getDeterminant33(data.at(0), data.at(1), data.at(3), data.at(4), data.at(5), data.at(7), data.at(12),
			data.at(13), data.at(15));
		Data d23 = -getDeterminant33(data.at(0), data.at(1), data.at(2), data.at(4), data.at(5), data.at(6),
			data.at(12), data.at(13), data.at(14));

		Data d30 = -getDeterminant33(data.at(1), data.at(2), data.at(3), data.at(5), data.at(6), data.at(7), data.at(9),
			data.at(10), data.at(11));
		Data d31 = getDeterminant33(data.at(0), data.at(2), data.at(3), data.at(4), data.at(6), data.at(7), data.at(8),
			data.at(10), data.at(11));
		Data d32 = -getDeterminant33(data.at(0), data.at(1), data.at(3), data.at(4), data.at(5), data.at(7), data.at(8),
			data.at(9), data.at(11));
		Data d33 = getDeterminant33(data.at(0), data.at(1), data.at(2), data.at(4), data.at(5), data.at(6), data.at(8),
			data.at(9), data.at(10));

		// Transpose and divide by the determinant.
		data.at(0) = d00 * invDeterminant;
		data.at(1) = d10 * invDeterminant;
		data.at(2) = d20 * invDeterminant;
		data.at(3) = d30 * invDeterminant;
		data.at(4) = d01 * invDeterminant;
		data.at(5) = d11 * invDeterminant;
		data.at(6) = d21 * invDeterminant;
		data.at(7) = d31 * invDeterminant;
		data.at(8) = d02 * invDeterminant;
		data.at(9) = d12 * invDeterminant;
		data.at(10) = d22 * invDeterminant;
		data.at(11) = d32 * invDeterminant;
		data.at(12) = d03 * invDeterminant;
		data.at(13) = d13 * invDeterminant;
		data.at(14) = d23 * invDeterminant;
		data.at(15) = d33 * invDeterminant;
	}

	template<typename Data>
	array<Data, SimpleMatrix44<>::SIZE> SimpleMatrix44<Data>::multiply(const array<Data, SIZE>& lhs
		, const array<Data, SIZE>& rhs) const
	{
		array < Data, SIZE > product;

		// For every row in the left hand matrix.
		for (unsigned int row = 0; row < HEIGHT; row++)
		{
			// For every column in the right hand matrix.
			for (unsigned int column = 0; column < WIDTH; column++)
			{
				Data sum = 0;

				// For every element in the current row of the left hand matrix and every element in the current column
				// of the right hand matrix.
				for (unsigned int element = 0; element < WIDTH; element++)
				{
					// Add the product of the two to the value for the new matrix.
					sum += lhs.at(row + (element * HEIGHT)) * rhs.at((column * WIDTH) + element);
				}

				product.at((column * WIDTH) + row) = sum;
			}
		}

		return product;
	}

	template<typename Data>
	array<Data, SimpleMatrix44<>::HEIGHT> SimpleMatrix44<Data>::multiplyWithVector(
		const array<Data, SimpleMatrix44<>::SIZE>& lhs, const array<Data, SimpleMatrix44<>::HEIGHT>& rhs) const
	{
		array < Data, HEIGHT > product;

		// For every row in the matrix.
		for (unsigned int row = 0; row < HEIGHT; row++)
		{
			Data sum = 0;

			// For every element in the vector and every element in the current row of the matrix.
			for (unsigned int element = 0; element < HEIGHT; element++)
			{
				// Add the product of the two to the value for the new vector.
				sum += lhs.at(row + (element * HEIGHT)) * rhs.at(element);
			}

			product.at(row) = sum;
		}

		return product;
	}

	template<typename Data>
	unique_ptr<Matrix<Data, SimpleMatrix44<>::SIZE> > SimpleMatrix44<Data>::operator*(
		const Matrix<Data, SIZE>& rhs) const
	{
		return unique_ptr<SimpleMatrix44<Data> >(new SimpleMatrix44<Data>(multiply(data, rhs.getData())));
	}

	template<typename Data>
	unique_ptr<Vector<Data, SimpleMatrix44<>::HEIGHT> > SimpleMatrix44<Data>::operator*(
		const Vector<Data, HEIGHT>& rhs) const
	{
		return unique_ptr<SimpleVector4<Data> >(new SimpleVector4<Data>(multiplyWithVector(data, rhs.getData())));
	}

	template<typename Data>
	Matrix<Data, SimpleMatrix44<>::SIZE>& SimpleMatrix44<Data>::operator*=(const Matrix<Data, SIZE>& rhs)
	{
		data = multiply(data, rhs.getData());

		return *this;
	}

	template<typename Data>
	void SimpleMatrix44<Data>::setIdentity()
	{
		data.at(0) = 1;
		data.at(1) = 0;
		data.at(2) = 0;
		data.at(3) = 0;

		data.at(4) = 0;
		data.at(5) = 1;
		data.at(6) = 0;
		data.at(7) = 0;

		data.at(8) = 0;
		data.at(9) = 0;
		data.at(10) = 1;
		data.at(11) = 0;

		data.at(12) = 0;
		data.at(13) = 0;
		data.at(14) = 0;
		data.at(15) = 1;
	}

	template<typename Data>
	string SimpleMatrix44<Data>::toString() const
	{
		string matrixString = "";

		matrixString += "-------------------------\n";
		matrixString += "| " + boost::lexical_cast<string>(data.at(0)) + " | " + boost::lexical_cast<string>(data.at(4))
			+ " | " + boost::lexical_cast<string>(data.at(8)) + " | " + boost::lexical_cast<string>(data.at(12))
			+ " |\n";
		matrixString += "-------------------------\n";
		matrixString += "| " + boost::lexical_cast<string>(data.at(1)) + " | " + boost::lexical_cast<string>(data.at(5))
			+ " | " + boost::lexical_cast<string>(data.at(9)) + " | " + boost::lexical_cast<string>(data.at(13))
			+ " |\n";
		matrixString += "-------------------------\n";
		matrixString += "| " + boost::lexical_cast<string>(data.at(2)) + " | " + boost::lexical_cast<string>(data.at(6))
			+ " | " + boost::lexical_cast<string>(data.at(10)) + " | " + boost::lexical_cast<string>(data.at(14))
			+ " |\n";
		matrixString += "-------------------------\n";
		matrixString += "| " + boost::lexical_cast<string>(data.at(3)) + " | " + boost::lexical_cast<string>(data.at(7))
			+ " | " + boost::lexical_cast<string>(data.at(11)) + " | " + boost::lexical_cast<string>(data.at(15))
			+ " |\n";
		matrixString += "-------------------------\n";

		return matrixString;
	}

	template<typename Data>
	void SimpleMatrix44<Data>::transpose()
	{
		Data temp = -1;

		temp = data.at(1);
		data.at(1) = data.at(4);
		data.at(4) = temp;

		temp = data.at(2);
		data.at(2) = data.at(8);
		data.at(8) = temp;

		temp = data.at(3);
		data.at(3) = data.at(12);
		data.at(12) = temp;

		temp = data.at(6);
		data.at(6) = data.at(9);
		data.at(9) = temp;

		temp = data.at(7);
		data.at(7) = data.at(13);
		data.at(13) = temp;

		temp = data.at(11);
		data.at(11) = data.at(14);
		data.at(14) = temp;
	}
}
