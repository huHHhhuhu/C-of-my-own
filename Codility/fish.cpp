// ConsoleApplication22.cpp : 定義主控台應用程式的進入點。
//

//個人當下發現不用stack無法實現本題
//觀察到此題適合運用stack之LIFO特性，把預備比較下個fish的魚之大小(以upstream or downstream均可)放入stack中。
//分析出不同情況分別處理。如規則不明，以足量代表所有情況之sample來做分析 

#include "stdafx.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

//演算法觀察他人的後，自己改寫的，但結構沒有系統+目前還有錯
//int solution(vector<int> &A, vector<int> &B)
//{
//	int i = 0, upstream_alive = 0;
//	stack<int> downstream_alive; //初始為空
//
//	while ((unsigned)i < A.size())
//	{
//		while (downstream_alive.empty())
//		{
//			while (B[i] == 0 && (unsigned)i < A.size())
//			{
//				upstream_alive++;
//				i++;
//			}
//			break;
//		}
//
//		while (B[i] != 0 && (unsigned)i < A.size())
//		{
//			downstream_alive.push(A[i]);
//			i++;
//		}
//
//		while (!downstream_alive.empty() && B[i] == 0 && (unsigned)i < A.size())
//		{
//			while (A[i]>downstream_alive.top() && !downstream_alive.empty())
//				downstream_alive.pop();
//			if (downstream_alive.empty())upstream_alive++;
//			i++;
//		}
//	}
//	return (unsigned)upstream_alive + downstream_alive.size();
//}

//他人寫，結構很有系統，容易懂、debug!!猛
int solution(vector<int> &A, vector<int> &B) 
{
	stack<int> downstream_alive;
	int upstream_alive = 0;

	for (int i = 0; i < B.size(); ++i)
	{
		if (B[i] == 1) downstream_alive.push(i);
		else
		{
			while (!downstream_alive.empty())
			{
				if (downstream_alive.top() > A[i]) break;
				else downstream_alive.pop();
			}
			if (downstream_alive.empty()) upstream_alive++;
		}
	}
	return 	upstream_alive + downstream_alive.size();;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> A{ 4, 3, 2, 1, 5 };
	vector<int> B{ 0, 1, 0, 0, 0 };

	cout << solution(A, B) << endl;

	return 0;
}

