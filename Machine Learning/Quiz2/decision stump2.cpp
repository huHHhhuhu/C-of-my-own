#include <fstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define DEMENSION 9           //數據維度

char *file = "training.txt";
char *file_test = "testing.txt";

struct record {
	double input[DEMENSION];
	int output;
};

struct singleDemensionRecord {
	double input;
	int output;
};

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

//從檔讀取資料
void getData(ifstream & dataFile, vector<record> &data)
{
	while (!dataFile.eof()){
		record curRecord;
		for (int i = 0; i<DEMENSION; ++i){ dataFile >> curRecord.input[i]; }
		dataFile >> curRecord.output;
		data.push_back(curRecord);
	}
	dataFile.close();
}

//計算指定維度的樣本錯誤率
double calErr(vector<singleDemensionRecord>& singleDemensionVec, vector<Hypothesis>& hypo, int demension)
{
	int errCount = 0;
	int length = singleDemensionVec.size();

	for (int i = 0; i<length; ++i){
		if (singleDemensionVec[i].output != hypo[demension - 1].coef*sign(singleDemensionVec[i].input - hypo[demension - 1].threshold)){
			errCount++;
		}
	}

	return double(errCount) / double(length);
}

//single demension record的比較函數
bool recCompare(singleDemensionRecord & a, singleDemensionRecord & b)
{
	return a.input<b.input;
}

//將指定維度的資料提取出來並昇冪排列
void getInputByDemension(vector<record>& dataSet, vector<singleDemensionRecord>& singleDemensionVec, int demension)
{
	int recordSize = dataSet.size();
	singleDemensionRecord curRec;

	for (int i = 0; i<recordSize; ++i){
		curRec.input = dataSet[i].input[demension - 1];
		curRec.output = dataSet[i].output;
		singleDemensionVec.push_back(curRec);
	}

	sort(singleDemensionVec.begin(), singleDemensionVec.end(), recCompare);
}

//遍歷所有θ，找到最小的E-in並返回
double getMinErrIn(vector<singleDemensionRecord> & singleDemensionVec, vector<Hypothesis>& hypo, int demension, double & bestThres)
{
	double minErrIn = 1.0;
	double curErrIn;
	int recordSize = singleDemensionVec.size();

	for (int i = 0; i<recordSize - 1; ++i){
		hypo[demension - 1].threshold = double(singleDemensionVec[i].input + singleDemensionVec[i + 1].input) / 2.0;
		curErrIn = calErr(singleDemensionVec, hypo, demension);
		if (curErrIn<minErrIn){
			minErrIn = curErrIn;
			bestThres = hypo[demension - 1].threshold;
		}
	}

	return minErrIn;
}

//Decision Stump 演算法, 確定s和θ
void decisionStump(vector<record>& trainingSet, vector<record>& testSet, vector<Hypothesis>& hypo)
{
	int recordSize = trainingSet.size();
	int minErrInDem;
	double minErrIn = 1.1;

	for (int dem = 0; dem<DEMENSION; ++dem){

		vector<singleDemensionRecord> singleDemensionVec;
		double curMinErrIn;
		double bestThresPositive;
		double bestThresNegtive;
		double minErrInPositive;
		double minErrInNegtive;

		getInputByDemension(trainingSet, singleDemensionVec, dem + 1);

		hypo[dem].coef = 1;
		minErrInPositive = getMinErrIn(singleDemensionVec, hypo, dem + 1, bestThresPositive);

		hypo[dem].coef = -1;
		minErrInNegtive = getMinErrIn(singleDemensionVec, hypo, dem + 1, bestThresNegtive);

		if (minErrInPositive<minErrInNegtive){
			hypo[dem].coef = 1;
			curMinErrIn = minErrInPositive;
			hypo[dem].threshold = bestThresPositive;
		}
		else{
			hypo[dem].coef = -1;
			curMinErrIn = minErrInNegtive;
			hypo[dem].threshold = bestThresNegtive;
		}

		if (minErrIn>curMinErrIn){
			minErrIn = curMinErrIn;
			minErrInDem = dem + 1;
		}
	}

	cout << "The demension with min error is : " << minErrInDem << endl;
	cout << "min E-in = " << minErrIn << endl;
	vector<singleDemensionRecord> singleDemensionTestVec;
	getInputByDemension(testSet, singleDemensionTestVec, minErrInDem);
	cout << "min E-out = " << calErr(singleDemensionTestVec, hypo, minErrInDem) << endl << endl;
}


void main()
{
	srand((unsigned)time(NULL));

	vector<record> trainingSet;                      //訓練數據
	vector<record> testSet;                          //測試資料
	vector<Hypothesis> hypoVec(DEMENSION);           //每個維度一個hypothesis

	ifstream dataFile(file);
	ifstream testDataFile(file_test);

	if (dataFile.is_open() && testDataFile.is_open()){
		getData(dataFile, trainingSet);
		getData(testDataFile, testSet);
	}
	else{
		cerr << "ERROR ---> 檔打開失敗" << endl;
		exit(1);
	}

	decisionStump(trainingSet, testSet, hypoVec);
}

