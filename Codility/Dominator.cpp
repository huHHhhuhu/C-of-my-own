// Dominator.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> &A)
{
	stack<int> stack;
	int index, candidate, count = 0;

	if (A.size() == 0)
		return -1;

	//if a leader exist, it won't change after two elements are eliminated at every turn, so we can pick out a candidate at the final turn.
	for (size_t i = 0; i < A.size(); i++)
	{
		if (stack.size() == 0)
		{
			stack.push(A[i]);
			candidate = stack.top();
			index = i;
		}
		else if (stack.size() != 0)
		{
			if (A[i] != candidate)
				stack.pop();
			else if (A[i] == candidate)
				stack.push(A[i]);
		}
	}

	//candidate在A佔一半以上, 則為dominator(leader)
	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] == candidate)
			count++;
	}
	if (count>(int)(0.5 * A.size()))
		return index;
	else
		return -1;

	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> A{1,2,1 };
	cout << solution(A);

	return 0;
}