#pragma once
namespace Algebra
{
	long long binpow_rec(long long a, long long b)
	{
		if (b == 0)
		{
			return 1;
		}
		long long res = binpow_rec(a, b / 2);
		if (b % 2)
			return  res * res* a;
		return res * res;
	}

	long long binpow_mod(long long a, long long b, long long m)
	{
		a %= m;
		long long res = 1;
		while (b >= 1)
		{
			if (b & 1)
				res = res * a % m;
			a = a * a % m;
			b >>= 1;
		}
		return res;
	}

	long long binpow_brute(long long a, long long b)
	{
		long long res = 1;
		while (b >= 1)
		{
			if (b & 1)
				res = res * a;
			a = a * a;
			b >>= 1;
		}
		return res;
	}
}
