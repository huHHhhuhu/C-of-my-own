#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
 
using namespace std;
 
#define DEMENSION 5                //數據維度
 
int step= 0;                       //反覆運算次數
int index = 0;                     //當前資料條目索引
bool isFinished = false;           //反覆運算終止狀態
char *file = "training_data.txt";
 
struct record {
    double input[DEMENSION];   //輸入
    int output;                //輸出    
};
 
 
 
int sign(double x)
{
    //同Q15
}
 
void add(double *v1, double *v2, int demension)
{
    //同Q15
}
 
//兩個向量相乘,返回內積
double multiply(double *v1, double *v2, int demension)
{
    //同Q15
}
 
//向量與實數相乘，結果通過*result返回，不改變參與計算的向量
void multiply(double *result, double *v, double num, int demension)
{
    //同Q15
}
 
//對 traininig set 創建一個隨機排序
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
 
//讀取所有訓練資料
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
         
        //找到下一個錯誤記錄的index
    while( trainingSet[randIndexes[index]].output == 
        sign(multiply(weights,trainingSet[randIndexes[index]].input,DEMENSION)) ){ 
        if(index==length-1) {index = 0;}
        else                {index++;}
        if(index==start)    {isFinished = true; break;}  //沒發現錯誤，反覆運算結束
    }
 
    if(isFinished){
        return;
    }else{
        step++;
                 
                //更新: weights = weights + curOutput * curInput
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
 
        double weights[DEMENSION];      //權重向量
        vector<record> trainingSet;     //訓練數據
        vector<int> randIndexes;        //訪問資料的隨機索引清單
        ifstream dataFile(file);
 
        step = 0;            
        index = 0;               
        isFinished = false;   
 
        if(dataFile.is_open()){
            getData(dataFile,trainingSet);  
            setRandomOrder(trainingSet,randIndexes);
        }else{
            cerr<<"ERROR ---> 檔打開失敗"<<endl;
            exit(1);
        }
 
        for(int i=0;i<DEMENSION;++i){ weights[i] = 0.0; }
 
        PLA(trainingSet, randIndexes, weights);
        totalSteps += step;
    }
 
    cout<<"Average Step = "<<totalSteps/2000<<endl;
}

