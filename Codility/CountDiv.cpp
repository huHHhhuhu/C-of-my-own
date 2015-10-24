// ConsoleApplication19.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

int solution(int A, int B, int K) {
	// write your code in C99


	/*int i, count = 0;		(此寫法時間複雜度不合格)
	for (i = A; i <= B; i++){
	if (i % K == 0)
	count++;
	}
	return count;*/


	//藉觀察足夠列舉來找出規則，進而設計效能更佳的演算法
	/*int difference = B - A, CountDiv;		(此寫法後來發現規則太繁瑣，太花時間、精神、容易寫錯、不好debug，最後還是寫不正確，慘!建議以後先把演算法想完整再下手，避免浪費時間。)

	if (K % 2 == 0){
	if (difference % K == 1)
	CountDiv = (difference + 1) / K;
	else if (difference % K == 0){
	if (A % K == 1)CountDiv = difference / K;
	else if (A % K == 0)CountDiv = difference / K + 1;
	}
	else if (K % 2 == 1) {
	if (difference % K == 0){
	if (A%K == 0)CountDiv = difference / K + 1;
	else if (A%K == 1 || A%K == 2)CountDiv = difference / K;
	}
	else if (difference % K == 1){
	if (A%K == 1)CountDiv = (difference - 1) / K;
	else if (A%K == 0 || A%K == 2)CountDiv = ((difference - 1) / K) + 1;
	}
	else if (difference % K == 2)
	CountDiv = (difference + 1) / K;
	}
	}*/


	//if (A % K == 0) return (int)(B - A) / K + 1;	//(篇幅短效能又好的演算法，猛!It is completely a mathematic question. Not qualified for a 2-star problem.)
	//else return (int)(B - (A - A % K)) / K;


	return (B / K) - (A / K) + !(A % K); //(神之境界!)
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << solution(6, 11, 2) << endl; //6 8 10 =3
	return 0;
}

