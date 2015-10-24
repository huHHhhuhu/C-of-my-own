// ConsoleApplication16.cpp : 定義主控台應用程式的進入點。
//N is an integer within the range[2..100, 000];
//each element of array A is an integer within the range[−1, 000..1, 000]. ;

#include "stdafx.h" 
//#include <stdio.h>
//#include <stdlib.h>
#include "time.h"	// time.h =<ctime>
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

int solution(vector<int> &A){
	//int P_split, j, k, cur_diff, min_diff;

	//for (P_split = 1; P_split < (signed)A.size(); P_split++){
	//	int first_part = 0, second_part = 0;
	//	for (j = 0; j < P_split; j++)
	//		first_part += A[j];
	//	for (k = P_split; k < (signed)A.size(); k++)
	//		second_part += A[k];

	int first_part = 0, second_part = 0, i, P_split,  cur_diff, min_diff;
		for (i = 0; i < (signed)A.size(); i++)
			second_part += A[i];
		for (P_split = 1; P_split < (signed)A.size(); P_split++){	// adjusts the 2 sums
			second_part -= A[P_split-1];
			first_part += A[P_split-1];
			cur_diff = abs(first_part - second_part);
			if (P_split == 1)min_diff = cur_diff;//小心判斷式內不要寫成=
			if (cur_diff < min_diff)min_diff = cur_diff;
		}
		return min_diff;
	}

	int _tmain(int argc, _TCHAR* argv[])
	{
		srand((unsigned)time(NULL));

		int i, N;
		vector<int> A; //空A

		N = (int)((double)rand() / RAND_MAX * 99998 + 2);

		for (i = 0; i < N; i++){
			A.push_back((int)((double)rand() / RAND_MAX * 2000 - 1000));
		}
		cout << solution(A) << endl;

		return 0;
	}


