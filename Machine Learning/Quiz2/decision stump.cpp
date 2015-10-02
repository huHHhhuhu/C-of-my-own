#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define SAMPLE_SIZE  20      //樣本量

struct Hypothesis{
	int coef;
	double threshold;
};

//求數位的符號
int sign(double x)
{
	if (x<0)       return -1;
	else if (x>0) return 1;
	else         return -1;
}

//反轉數位的符號
int flipSign(int num)
{
	return num * (-1);
}

//計算樣本錯誤率
double calErrInSample(vector<double>& inputVec, vector<int>& outputVec, Hypothesis & hypo)
{
	int errCount = 0;

	for (int i = 0; i<SAMPLE_SIZE; ++i){
		if (outputVec[i] != hypo.coef*sign(inputVec[i] - hypo.threshold)){
			errCount++;
		}
	}

	return double(errCount) / double(SAMPLE_SIZE);
}

//計算全域錯誤率
double calErrOutSample(Hypothesis & hypo)
{
	return 0.5 + 0.3 * double(hypo.coef) * (abs(hypo.threshold) - 1.0);
}

//產生[-1,1]之間均勻分佈的亂數
double getRand()
{
	return 2.0 * double(rand()) / double(RAND_MAX) - 1.0;
}

//生成訓練資料
void getTrainingData(vector<double>& inputVec)
{
	for (int i = 0; i<SAMPLE_SIZE; ++i){
		inputVec.push_back(getRand());
	}
	//對inputVec做昇冪排列(sort函數預設昇冪)
	sort(inputVec.begin(), inputVec.end());
}

//根據f(x)產生輸出，有20%的出錯率
void calOutput(vector<double>& inputVec, vector<int>& outputVec)
{
	int output;
	double randNum;

	for (int i = 0; i<SAMPLE_SIZE; ++i){
		randNum = double(rand()) / double(RAND_MAX);  //[0,1];
		output = sign(inputVec[i]);
		if (randNum <= 0.2){
			output = flipSign(output);
		}
		outputVec.push_back(output);
	}
}

//遍歷所有θ，找到最小的E-in並返回
double getMinErrIn(vector<double>& inputVec, vector<int>& outputVec, Hypothesis & hypo, double & bestThres)
{
	double minErrIn = 1.0;
	double curErrIn;

	for (int i = 0; i<SAMPLE_SIZE - 1; ++i){
		hypo.threshold = double(inputVec[i] + inputVec[i + 1]) / 2.0;
		curErrIn = calErrInSample(inputVec, outputVec, hypo);
		if (curErrIn<minErrIn){
			minErrIn = curErrIn;
			bestThres = hypo.threshold;
		}
	}

	return minErrIn;
}

//Decision Stump 演算法, 確定s和θ
double decisionStump(vector<double>& inputVec, vector<int>& outputVec, Hypothesis & hypo)
{
	double minErrInPositive = 1.0;
	double minErrInNegtive = 1.0;
	double minErrIn;

	double bestThresPositive;
	double bestThresNegtive;

	hypo.coef = 1;
	minErrInPositive = getMinErrIn(inputVec, outputVec, hypo, bestThresPositive);

	hypo.coef = -1;
	minErrInNegtive = getMinErrIn(inputVec, outputVec, hypo, bestThresNegtive);

	if (minErrInPositive<minErrInNegtive){
		hypo.coef = 1;
		minErrIn = minErrInPositive;
		hypo.threshold = bestThresPositive;
	}
	else{
		hypo.coef = -1;
		minErrIn = minErrInNegtive;
		hypo.threshold = bestThresNegtive;
	}

	return minErrIn;
}


void main()
{
	srand((unsigned)time(NULL));

	double errInTotal = 0.0;
	double errOutTotal = 0.0;

	for (int i = 0; i<5000; ++i){
		vector<double> inputVec;
		vector<int> outputVec;
		Hypothesis hypo;

		getTrainingData(inputVec);
		calOutput(inputVec, outputVec);

		errInTotal += decisionStump(inputVec, outputVec, hypo);
		errOutTotal += calErrOutSample(hypo);

		cout << "-----------------第" << i + 1 << "次計算結束-------------------\n";
		cout << "s = " << hypo.coef << endl;
		cout << "θ= " << hypo.threshold << endl;
	}

	cout << "Average E-in = " << errInTotal / 5000 << "\n";
	cout << "Average E-out = " << errOutTotal / 5000 << "\n";
}

