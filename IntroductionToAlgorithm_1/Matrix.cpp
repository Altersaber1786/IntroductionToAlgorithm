#include "Matrix.h"

#include <iostream>

#define A11 Matrix<int>(A, n / 2, n / 2, 1, 1)
#define A12 Matrix<int>(A, n / 2, n / 2, 1, n/2 + 1)
#define A21 Matrix<int>(A, n / 2, n / 2, n/2 + 1, 1)
#define A22 Matrix<int>(A, n / 2, n / 2, n/2 + 1, n/2 + 1)

#define B11 Matrix<int>(B, n / 2, n / 2, 1, 1)
#define B12 Matrix<int>(B, n / 2, n / 2, 1, n/2 + 1)
#define B21 Matrix<int>(B, n / 2, n / 2, n/2 + 1, 1)
#define B22 Matrix<int>(B, n / 2, n / 2, n/2 + 1, n/2 + 1)

#define C11 Matrix<int>(C, n / 2, n / 2, 1, 1)
#define C12 Matrix<int>(C, n / 2, n / 2, 1, n/2 + 1)
#define C21 Matrix<int>(C, n / 2, n / 2, n/2 + 1, 1)
#define C22 Matrix<int>(C, n / 2, n / 2, n/2 + 1, n/2 + 1)

#define M1 StrassenMatrixMultiply(A11 + A22, B11 + B22)
#define M2 StrassenMatrixMultiply(A21 + A22, B11)
#define M3 StrassenMatrixMultiply(A11, B12 - B22)
#define M4 StrassenMatrixMultiply(A22, B21 - B11)
#define M5 StrassenMatrixMultiply(A11 + A12, B22)
#define M6 StrassenMatrixMultiply(A21 - A11, B11 + B12)
#define M7 StrassenMatrixMultiply(A12 - A22, B21 + B22)

using namespace My_Matrix;

void My_Matrix::Matrix<int>::Print()
{
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			if (this->operator()(i, j) >= 0)
				printf("%2d\t", operator()(i, j));
			else
				printf("%d\t", operator()(i, j));
		}
		printf("\n");
	}
}

void My_Matrix::Matrix<float>::Print()
{
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			if (this->operator()(i, j) >= 0)
				printf("%2f\t", operator()(i, j));
			else
				printf("%f\t", operator()(i, j));
		}
		printf("\n");
	}
}


Matrix<int> My_Matrix::StrassenMatrixMultiply(Matrix<int> A, Matrix<int> B)
{
	int n = A.rows;
	Matrix<int> C = Matrix<int>(n, n);
	if (n == 1)
		C(1, 1) = A(1, 1)*B(1, 1);
	else
	{
		C11 = M1 + M4 - M5 + M7;
		C12 = M3 + M5;
		C21 = M2 + M4;
		C22 = M1 - M2 + M3 + M6;
	}
	return C;
};


Matrix<int> My_Matrix::MatrixSorting(Matrix<int> A)
{
	unsigned int n = A.rows;
	if (n == 2)
	{
		if (A(1, 2) > A(2, 1)) {
			int temp = A(1, 2);
			A(1, 2) = A(2, 1);
			A(2, 1) = temp;
			return A;
		}
		return A;
	}
	
	A11 = MatrixSorting(A11);
	A12 = MatrixSorting(A12);
	A21 = MatrixSorting(A21);
	A22 = MatrixSorting(A22);

	return A;
}

//This is to check if the matrix is eligible for strassen Algorithm, which is useless so far
bool IsPowerOf2(uint32_t x)
{
	return x > 0 && 0 == (1 << 30) % x;
}


Matrix<int> My_Matrix::SquareMatrixPow(Matrix<int> A, uint32_t n)
{
	assert(A.rows == A.columns);
	Matrix<int> temp = Matrix<int>(A.rows, A.rows);
	if (n == 0)
		return temp;
	for (uint32_t i = 0; i < n; i++)
		temp = temp * A;
	return temp;
};

bool My_Matrix::Matrix<float>::LU_Factorize(Matrix& L, Matrix& U)
{
	L = Matrix(rows, rows);
	if (rows == columns && U.rows == U.columns && L.columns == rows && U.columns == rows)
	{
		U = *this;
		for (int i = 1; i <= rows; i++)
		{
			for (int j = i + 1; j <= rows; j++)
			{
				if (U(i, i) == 0)
				{
					std::cout << "A pivot is equal to zero\n";
					return false;
				}
				float m = (-1.0f)*(float)(U(j, i) / U(i, i));
				L(j, i) = -m;
				bool hasNonzero = false;
				for (int k = 1; k <= columns; k++)
				{
					U(j, k) = U(j, k) + m * U(i, k);
					if (U(j, k) != 0) hasNonzero = true;
				}

				if (hasNonzero == false)
				{
					std::cout << "Matrix is singular, cannot be factorized\n";
				}
			}
		}
		return true;
	}
	std::cout << "The size of these matrices are not equal, or they are not square";
	return false;
};