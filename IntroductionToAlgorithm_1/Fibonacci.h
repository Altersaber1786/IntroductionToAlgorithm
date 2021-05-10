#pragma once
#include "Matrix.h"
namespace Fibonacci	
{

	int A[] = { 1, 1, 1, 0 };
	int F[] = { 1 ,0 };
	My_Matrix::Matrix<int> P = My_Matrix::Matrix<int>(2, 2, A);

	int fibonacci(uint32_t n);
	int fibonacci_decode(std::string s);
	std::string fibonacci_encode(uint32_t x);

}
