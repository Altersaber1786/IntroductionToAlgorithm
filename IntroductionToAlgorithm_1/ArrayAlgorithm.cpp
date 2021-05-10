#include "ArrayAlgorithm.h"

using namespace My_Array;

MAX_SUBARRAY_RETURN My_Array::FIND_MAX_CROSSING_SUBARRRAY(int A[], int low, int mid, int high)
{
	int sum = 0;
	MAX_SUBARRAY_RETURN result;
	result.sum = std::numeric_limits<int>::lowest();
	result.low_idex = mid;
	result.high_idex = mid + 1;
	for (int i = mid; i >= low; i--)
	{
		sum += A[i];
		if (result.sum < sum)
		{
			result.sum = sum;
			result.low_idex = i;
		};
	}
	sum = result.sum;
	result.sum += A[mid + 1];
	for (int i = mid + 1; i <= high; i++)
	{
		sum += A[i];
		if (result.sum < sum)
		{
			result.sum = sum;
			result.high_idex = i;
		}
	}
	return result;
}

MAX_SUBARRAY_RETURN My_Array::FIND_MAX_SUBARRAY_RECURSIVE(int A[], int low, int high)
{
	MAX_SUBARRAY_RETURN recur_result;
	if (low == high)
	{
		recur_result.low_idex = low;
		recur_result.high_idex = high;
		recur_result.sum = A[low];
		return recur_result;
	}
	int mid = (high + low) / 2;

	MAX_SUBARRAY_RETURN max_left_array = FIND_MAX_SUBARRAY_RECURSIVE(A, low, mid);
	MAX_SUBARRAY_RETURN max_right_array = FIND_MAX_SUBARRAY_RECURSIVE(A, mid + 1, high);
	MAX_SUBARRAY_RETURN max_crossing_array = FIND_MAX_CROSSING_SUBARRRAY(A, low, mid, high);

	if (max_left_array.sum >= max_crossing_array.sum && max_left_array.sum >= max_right_array.sum)
		return max_left_array;
	else if (max_right_array.sum >= max_crossing_array.sum && max_right_array.sum >= max_left_array.sum)
	{
		return max_right_array;
	}

	else return max_crossing_array;
}

MAX_DIFFERENCE_RETURN My_Array::FIND_MAX_DIFFERENCE_BRUTE_FORCE(int A[], int num)
{
	MAX_DIFFERENCE_RETURN result;
	result.difference = std::numeric_limits<int>::lowest();
	int diff;
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			diff = A[j] - A[i];
			if (result.difference < diff)
			{
				result.difference = diff;
				result.low_index = i;
				result.high_index = j;
			}
		}
	}

	return  result;
};

MAX_DIFFERENCE_RETURN My_Array::FIND_MAX_DIFFERENCE_RECURSIVE(int A[], int num)
{
	MAX_DIFFERENCE_RETURN result;
	int *B = new int[num - 1];
	for (int i = 1; i < num; i++)
	{
		B[i - 1] = A[i] - A[i - 1];
	}
	MAX_SUBARRAY_RETURN max_sub = FIND_MAX_SUBARRAY_RECURSIVE(B, 0, num - 2);
	delete B;
	result.difference = max_sub.sum;
	result.low_index = max_sub.low_idex;
	result.high_index = max_sub.high_idex + 1;
	return result;
}

MAX_DIFFERENCE_RETURN My_Array::FIND_MAX_DIFFERENCE_LINEAR(int A[], int num)
{
	MAX_DIFFERENCE_RETURN result;
	int *B = new int[num - 1];
	for (int i = 1; i < num; i++)
	{
		B[i - 1] = A[i] - A[i - 1];
	}
	int sub_sum = 0;
	MAX_SUBARRAY_RETURN max_sub;
	max_sub.low_idex = 0;
	max_sub.high_idex = 0;
	max_sub.sum = std::numeric_limits<int>::lowest();
	for (int i = 0; i <= num - 2; i++)
	{
		sub_sum += B[i];
		if (sub_sum > max_sub.sum)
		{
			if (max_sub.high_idex != max_sub.low_idex)
			{
				int new_max_sub_sum = 0;
				for (int j = i; j >= max_sub.high_idex + 1; j--)
				{
					new_max_sub_sum += B[j];
					if (new_max_sub_sum > max_sub.sum)
					{
						max_sub.sum = new_max_sub_sum;
						max_sub.low_idex = j;
						sub_sum = max_sub.sum;
					}
				}
				max_sub.high_idex = i;
			}
			else
				max_sub.high_idex = i;
		}
	}
	result.difference = max_sub.sum;
	result.low_index = max_sub.low_idex;
	result.high_index = max_sub.high_idex + 1;
	delete B;
	return result;
}
