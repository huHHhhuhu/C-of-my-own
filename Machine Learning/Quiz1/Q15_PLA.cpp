#include <fstream>
#include <iostream>
#include <vector>
#include "stdafx.h"

using namespace std;	//本script省略的class前綴為std

#define DEMENSION 5                //X數據維度

double weights[DEMENSION];         //權重向量
int step = 0;                       //反覆運算次數
int length = 0;                    //數據條目個數
int index = 0;                     //當前資料條目索引
bool isFinished = false;           //反覆運算終止狀態
char *file = "training_data.txt";  //11-1

struct record {
	double input[DEMENSION];   //輸入
	int output;                //輸出    
};
vector<record> trainingSet;        //訓練數據集


int sign(double x)
{
	if (x<0)       return -1;
	else if (x>0) return 1;
	else         return -1;
}

//兩個向量相加，更新第一個向量
void add(double *v1, double *v2, int demension)
{
	for (int i = 0; i<demension; ++i){ v1[i] = v1[i] + v2[i]; }
}

//兩個向量相乘,返回內積
double multiply(double *v1, double *v2, int demension)
{
	double innerProd = 0.0;
	for (int i = 0; i<demension; ++i){
		innerProd += v1[i] * v2[i];
	}
	return innerProd;
}

//向量與實數相乘，結果通過*result返回，不改變參與計算的向量
void multiply(double *result, double *v, double num, int demension)  
{
	for (int i = 0; i<demension; ++i){ result[i] = v[i] * num; }
}

//讀取所有訓練資料
void getData(ifstream & dataFile) //Q
{
	while (!dataFile.eof()){   //會一直跑while直到文件尾(遇到EOF(End Of Line)字符)
		record curRecord; //包含五個元素
		curRecord.input[0] = 1; //input部分只需要4-d，所以1st虛設1
		for (int i = 1; i<DEMENSION; ++i){ dataFile >> curRecord.input[i]; } 
		dataFile >> curRecord.output; 
		trainingSet.push_back(curRecord); //不斷把curRecord的元素存到trainingSet的陣列尾，直到文件讀完跳出while
	}
	dataFile.close(); //關閉文件
	length = trainingSet.size(); //返回trainingSet元素"組"數
}

void PLA()
{
	int start = index;
	double curInput[DEMENSION];

	//找下一個錯誤的index，如果發現已經輪完一遍都沒發現錯誤則break
	while (trainingSet[index].output ==
		sign(multiply(weights,trainingSet[index].input,DEMENSION))) //input用五維資料下去算竟然沒出錯?
	{
		if (index == length - 1) { index = 0; } //使從頭開始驗
		else            { index++; }
		if (index == start)    { isFinished = true; break; }  //沒發現錯誤，反覆運算結束
	}

	//無須更新則回傳總更新次數，否則更新並繼續跑
	if (isFinished){
		cout << "計算結果：step = " << step << ", weights = \n";
		for (int i = 0; i<DEMENSION; ++i){ cout << weights[i] << endl; } 
		return;
	}
	else{
		step++;

		//更新: weights = weights + curOutput * curInput
		multiply(curInput, trainingSet[index].input, trainingSet[index].output, DEMENSION); //回傳的curInput已經和curOutput相乘了
		add(weights, curInput, DEMENSION);   //回傳的curInput已經和curOutput相乘了

		if (index == length - 1) { index = 0; }
		else            { index++; }

		PLA();
	}
	return;
}

void main()
{
	ifstream dataFile(file);  //從指定的檔案file讀取數據並創建一個fstream叫做dataFile

	if (dataFile.is_open()){  //檢查是否成功打開
		getData(dataFile);
	}
	else{
		cerr << "ERROR ---> 檔打開失敗" << endl; //錯誤警告
		exit(1); //Terminates the process normally, performing the regular cleanup for terminating programs. 好像沒效果?
	}

	for (int i = 0; i<DEMENSION; ++i){ weights[i] = 0.0; } //給定條件: initialize W = 0 

	PLA(); //start training
}

