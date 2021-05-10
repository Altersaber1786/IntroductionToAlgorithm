#include "HashTable.h"

using namespace hashing;
UINT hashing::knuth(UINT key, uint32_t m)
{
	unsigned short p = 1;
	uint32_t x = (1 << 31);
	while (!(m & x))
	{
		m <<= 1;
		p++;
	}
	assert(p >= 0 && p <= 32);

	const uint32_t knuth = 2654435769;
	return (key * knuth) >> p;
}

bool hashing::isPowerOf2(UINT n)
{
	return (0 == (1 << 30) % n);
}
UINT hashing::simpleKnuth(UINT key, uint32_t m)
{
	const double A = 0.61803398875;
	double y = (key * A);
	y = y - floor(y);
	return static_cast<UINT>(y*m);
}