//==============================================================================
// This software is distributed under The Unlicense. 
// For more information, please refer to <http://unlicense.org/>
//==============================================================================

#pragma once

#include "MatrixModule.hpp"

namespace mathter {


template <class T, int Rows, int Columns, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
class MatrixSquare {
	using MatrixT = Matrix<T, Rows, Columns, Order, Layout, Packed>;
public:
	friend MatrixT;
	using Inherit = impl::Empty<MatrixSquare>;
};

template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
class MatrixSquare<T, Dim, Dim, Order, Layout, Packed> {
	using MatrixT = Matrix<T, Dim, Dim, Order, Layout, Packed>;
	MatrixT& self() { return *static_cast<MatrixT*>(this); }
	const MatrixT& self() const { return *static_cast<const MatrixT*>(this); }
public:
	T Trace() const;
	T Determinant() const;
	MatrixT& Transpose();
	MatrixT& Invert();
	MatrixT Inverse() const;
public:
	friend MatrixT;
	using Inherit = MatrixSquare;
};




template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
T MatrixSquare<T, Dim, Dim, Order, Layout, Packed>::Trace() const {
	T sum = self()(0, 0);
	for (int i = 1; i < Dim; ++i) {
		sum += self()(i, i);
	}
	return sum;
}

template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
T MatrixSquare<T, Dim, Dim, Order, Layout, Packed>::Determinant() const {
	// only works for Crout's algorithm, where U's diagonal is 1s
	MatrixT L, U;
	self().DecomposeLU(L, U);
	T prod = L(0, 0);
	for (int i = 1; i < L.RowCount(); ++i) {
		prod *= L(i, i);
	}
	return prod;
}

template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
auto MatrixSquare<T, Dim, Dim, Order, Layout, Packed>::Transpose() -> MatrixT& {
	self() = self().Transposed();
	return self();
}

template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
auto MatrixSquare<T, Dim, Dim, Order, Layout, Packed>::Invert() -> MatrixT& {
	*this = Inverse();
	return self();
}

template <class T, int Dim, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
auto MatrixSquare<T, Dim, Dim, Order, Layout, Packed>::Inverse() const -> MatrixT {
	MatrixT ret;

	mathter::DecompositionLU<T, Dim, Order, Layout, Packed> LU = self().DecompositionLU();

	Vector<T, Dim, Packed> b(0);
	Vector<T, Dim, Packed> x;
	for (int col = 0; col < Dim; ++col) {
		b(std::max(0, col - 1)) = 0;
		b(col) = 1;
		LU.Solve(x, b);
		for (int i = 0; i < Dim; ++i) {
			ret(i, col) = x(i);
		}
	}

	return ret;
}


}