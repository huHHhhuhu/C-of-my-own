#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> &A)
{
	int preserve_array_sum = 0, current_max_slice = 0, negative_quantity = 0;

	//not全部元素<0的情況:
	for (size_t i = 0; i < A.size(); i++)
	{
		preserve_array_sum = max(0, preserve_array_sum + A[i]);
		//if preserve_array_sum>0, 則目前保留的array保留待審查, 		//else if preserve_array_sum <= 0, 則捨去保留array。
		if (preserve_array_sum>current_max_slice)
			current_max_slice = preserve_array_sum;
	}

	//if全部元素<0的情況:
	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] < 0) negative_quantity++;
	}
	if (negative_quantity == A.size())
	{
		sort(A.begin(), A.end());
		return A.back();
	}
	return current_max_slice;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> A{ 3, 2, -6, 4, 0 };
	cout << solution(A) << endl;

	return 0;
}