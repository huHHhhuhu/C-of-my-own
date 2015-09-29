#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
 
using namespace std;
 
#define DEMENSION 5                //�ƾں���
 
int step= 0;                       //���йB�⦸��
int index = 0;                     //��e��Ʊ��د���
bool isFinished = false;           //���йB��פ�A
char *file = "training_data.txt";
 
struct record {
    double input[DEMENSION];   //��J
    int output;                //��X    
};
 
 
 
int sign(double x)
{
    //�PQ15
}
 
void add(double *v1, double *v2, int demension)
{
    //�PQ15
}
 
//��ӦV�q�ۭ�,��^���n
double multiply(double *v1, double *v2, int demension)
{
    //�PQ15
}
 
//�V�q�P��Ƭۭ��A���G�q�L*result��^�A�����ܰѻP�p�⪺�V�q
void multiply(double *result, double *v, double num, int demension)
{
    //�PQ15
}
 
//�� traininig set �Ыؤ@���H���Ƨ�
void setRandomOrder(vector<record> &trainingSet, vector<int> &randIndexes)
{
    srand((unsigned)time(NULL)); 
    int length = trainingSet.size(); 
    vector<bool> assignedIndexes(length,false);    
 
    for(int i=0;i<length;++i){
        int randIndex = rand()%length;
        while(assignedIndexes[randIndex]==true){
            randIndex = rand()%length;    
        }
        randIndexes.push_back(randIndex); 
        assignedIndexes[randIndex] = true;        
    }
}
 
//Ū���Ҧ��V�m���
void getData(ifstream & dataFile, vector<record> &trainingSet)
{
    while(!dataFile.eof()){
        record curRecord;
        curRecord.input[0] = 1;      
        for(int i=1;i<DEMENSION;++i){ dataFile>>curRecord.input[i]; }
        dataFile>>curRecord.output;
        trainingSet.push_back(curRecord);
    }
    dataFile.close();   
}
 
 
void PLA(vector<record> &trainingSet, vector<int> &randIndexes, double *weights)
{
    int length = trainingSet.size();
    int start = index;   
    double curInput[DEMENSION];
         
        //���U�@�ӿ��~�O����index
    while( trainingSet[randIndexes[index]].output == 
        sign(multiply(weights,trainingSet[randIndexes[index]].input,DEMENSION)) ){ 
        if(index==length-1) {index = 0;}
        else                {index++;}
        if(index==start)    {isFinished = true; break;}  //�S�o�{���~�A���йB�⵲��
    }
 
    if(isFinished){
        return;
    }else{
        step++;
                 
                //��s: weights = weights + curOutput * curInput
        multiply( curInput, trainingSet[randIndexes[index]].input, 
            trainingSet[randIndexes[index]].output, DEMENSION );  
        add( weights, curInput, DEMENSION );    
 
        if(index==length-1) {index = 0;}
        else                {index++;}
 
        PLA(trainingSet, randIndexes, weights);   
    }
    return;
}
 
void main()
{
    int totalSteps = 0;
 
    for(int i=0;i<2000;++i){
 
        double weights[DEMENSION];      //�v���V�q
        vector<record> trainingSet;     //�V�m�ƾ�
        vector<int> randIndexes;        //�X�ݸ�ƪ��H�����޲M��
        ifstream dataFile(file);
 
        step = 0;            
        index = 0;               
        isFinished = false;   
 
        if(dataFile.is_open()){
            getData(dataFile,trainingSet);  
            setRandomOrder(trainingSet,randIndexes);
        }else{
            cerr<<"ERROR ---> �ɥ��}����"<<endl;
            exit(1);
        }
 
        for(int i=0;i<DEMENSION;++i){ weights[i] = 0.0; }
 
        PLA(trainingSet, randIndexes, weights);
        totalSteps += step;
    }
 
    cout<<"Average Step = "<<totalSteps/2000<<endl;
}

