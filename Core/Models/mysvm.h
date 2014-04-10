#ifndef MYSVM_H
#define MYSVM_H
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#include "libsvm/svm.h"
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;
class MySVM
{
private:
    string baseDir;
    string featureName;

    int featurType; // 0--dct 1---lbpspm 2---gabor
    //-----------feature extraction parameters
     string imgDir ;                         //训练图像的路径  ="/home/lsq/data/image/";


    string featurePath;                      //path = baseDir + featureName +?
    string modelPath;
    string labelPath;
    //-----------train parameter
    struct svm_parameter param;		            // svm参数
    struct svm_problem prob;		            // 读入的训练数据
    struct svm_node *x_space;
//    string input_file_name;                 // 训练的特征路径 ="/home/lsq/data/feature/svm/dct-svm.fe";//
//    string model_file_name;                 //模型存储的位置="/ home/lsq/heart_scale.model";
    int cross_validation;
    int nr_fold;

    char *line1 ;
    int max_line1_len;


    struct svm_model *model;                 // train & predict

    //----------------------predict parameter
    FILE *input;                        //要预测的数据
    FILE *output;                       //结果存放的位置
    struct svm_node *x;
    int max_nr_attr;
    int predict_probability ;


public:
    MySVM();
    ~MySVM();


public:  //-------------feature extraction------
    void featureExtraction();               //svm特征提取
    bool setFeatureType(int t);
    void switchFeature();



public: //----------------train------------------
    void freeTrainParameter();
    void setTrainParameter();//  分类\预测
    void read_problem(const char *filename);  //读入训练数据
    void train();
    void myfree();

public : //------------------predict--------------
    bool predict(const string &imgPath,vector<string>& labels);
    void predict(FILE *input, FILE *output); //批处理
    bool classify(const string &imgPath,vector<string>& labels);

    //--

     bool readLabels();
     char* readline1(FILE *input);
public://demo
     void easyDemo();

   private:
     vector<string> svmlabels;

};

#endif // SVM_H
