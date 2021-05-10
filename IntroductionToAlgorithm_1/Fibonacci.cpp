#include "Fibonacci.h"

using namespace Fibonacci;

int Fibonacci::fibonacci(uint32_t n)
{
	return My_Matrix::SquareMatrixPow(P, n)(1, 2);
};

int  Fibonacci::fibonacci_decode(std::string s)
{
	int res = 0, i = 0;
	while (s[i + 1] != '\0')
	{
		assert(s[i] == '0' || s[i] == '1');
		res += (s[i] - 48) * fibonacci(i + 2);
		i++;
	}
	return res;
}

std::string  Fibonacci::fibonacci_encode(uint32_t x)
{
	std::string s;

	return s;
}
