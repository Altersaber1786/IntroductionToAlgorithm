#pragma once
#include <limits>
#include <vector>
#include <cassert>
namespace My_Array
{
	struct MAX_SUBARRAY_RETURN
	{
		int low_idex = 0;
		int high_idex = 0;
		int sum = 0;
	};

	struct MAX_DIFFERENCE_RETURN
	{
		int low_index = 0;
		int high_index = 0;
		int difference = 0;
	};


	MAX_SUBARRAY_RETURN FIND_MAX_CROSSING_SUBARRRAY(int A[], int low, int mid, int high);

	MAX_SUBARRAY_RETURN FIND_MAX_SUBARRAY_RECURSIVE(int A[], int low, int high);

	MAX_DIFFERENCE_RETURN FIND_MAX_DIFFERENCE_BRUTE_FORCE(int A[], int num);

	MAX_DIFFERENCE_RETURN FIND_MAX_DIFFERENCE_RECURSIVE(int A[], int num);

	MAX_DIFFERENCE_RETURN FIND_MAX_DIFFERENCE_LINEAR(int A[], int num);


	template <typename T>
	std::vector<T> ApplyPermutation(std::vector<T> origin, std::vector<unsigned int> Permutation)
	{

		assert(origin.size() == Permutation.size());
		std::vector<T> res;
		for (unsigned int i = 0; i < origin.size(); i++)
		{
			res.push_back(origin[Permutation[i]]);
		}
		return res;
	}

	template <typename T>
	std::vector<T> ApplyPermutationMultipleTimes(std::vector<T> origin, std::vector<unsigned int> Permutation, unsigned int k)
	{
		assert(origin.size() == Permutation.size());
		std::vector<T> res = origin;
		while (k > 0)
		{
			if (k & 1)
				res = ApplyPermutation(res, Permutation);
			Permutation = ApplyPermutation(Permutation, Permutation);
			k >>= 1;
		}
		return res;
	}
}

