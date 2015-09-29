#include <fstream>
#include <iostream>
#include <vector>
#include "stdafx.h"

using namespace std;	//��script�ٲ���class�e��std

#define DEMENSION 5                //X�ƾں���

double weights[DEMENSION];         //�v���V�q
int step = 0;                       //���йB�⦸��
int length = 0;                    //�ƾڱ��حӼ�
int index = 0;                     //��e��Ʊ��د���
bool isFinished = false;           //���йB��פ�A
char *file = "training_data.txt";  //11-1

struct record {
	double input[DEMENSION];   //��J
	int output;                //��X    
};
vector<record> trainingSet;        //�V�m�ƾڶ�


int sign(double x)
{
	if (x<0)       return -1;
	else if (x>0) return 1;
	else         return -1;
}

//��ӦV�q�ۥ[�A��s�Ĥ@�ӦV�q
void add(double *v1, double *v2, int demension)
{
	for (int i = 0; i<demension; ++i){ v1[i] = v1[i] + v2[i]; }
}

//��ӦV�q�ۭ�,��^���n
double multiply(double *v1, double *v2, int demension)
{
	double innerProd = 0.0;
	for (int i = 0; i<demension; ++i){
		innerProd += v1[i] * v2[i];
	}
	return innerProd;
}

//�V�q�P��Ƭۭ��A���G�q�L*result��^�A�����ܰѻP�p�⪺�V�q
void multiply(double *result, double *v, double num, int demension)  
{
	for (int i = 0; i<demension; ++i){ result[i] = v[i] * num; }
}

//Ū���Ҧ��V�m���
void getData(ifstream & dataFile) //Q
{
	while (!dataFile.eof()){   //�|�@���]while�������(�J��EOF(End Of Line)�r��)
		record curRecord; //�]�t���Ӥ���
		curRecord.input[0] = 1; //input�����u�ݭn4-d�A�ҥH1st��]1
		for (int i = 1; i<DEMENSION; ++i){ dataFile >> curRecord.input[i]; } 
		dataFile >> curRecord.output; 
		trainingSet.push_back(curRecord); //���_��curRecord�������s��trainingSet���}�C���A������Ū�����Xwhile
	}
	dataFile.close(); //�������
	length = trainingSet.size(); //��^trainingSet����"��"��
}

void PLA()
{
	int start = index;
	double curInput[DEMENSION];

	//��U�@�ӿ��~��index�A�p�G�o�{�w�g�����@�M���S�o�{���~�hbreak
	while (trainingSet[index].output ==
		sign(multiply(weights,trainingSet[index].input,DEMENSION))) //input�Τ�����ƤU�h�⳺�M�S�X��?
	{
		if (index == length - 1) { index = 0; } //�ϱq�Y�}�l��
		else            { index++; }
		if (index == start)    { isFinished = true; break; }  //�S�o�{���~�A���йB�⵲��
	}

	//�L����s�h�^���`��s���ơA�_�h��s���~��]
	if (isFinished){
		cout << "�p�⵲�G�Gstep = " << step << ", weights = \n";
		for (int i = 0; i<DEMENSION; ++i){ cout << weights[i] << endl; } 
		return;
	}
	else{
		step++;

		//��s: weights = weights + curOutput * curInput
		multiply(curInput, trainingSet[index].input, trainingSet[index].output, DEMENSION); //�^�Ǫ�curInput�w�g�McurOutput�ۭ��F
		add(weights, curInput, DEMENSION);   //�^�Ǫ�curInput�w�g�McurOutput�ۭ��F

		if (index == length - 1) { index = 0; }
		else            { index++; }

		PLA();
	}
	return;
}

void main()
{
	ifstream dataFile(file);  //�q���w���ɮ�fileŪ���ƾڨóЫؤ@��fstream�s��dataFile

	if (dataFile.is_open()){  //�ˬd�O�_���\���}
		getData(dataFile);
	}
	else{
		cerr << "ERROR ---> �ɥ��}����" << endl; //���~ĵ�i
		exit(1); //Terminates the process normally, performing the regular cleanup for terminating programs. �n���S�ĪG?
	}

	for (int i = 0; i<DEMENSION; ++i){ weights[i] = 0.0; } //���w����: initialize W = 0 

	PLA(); //start training
}

