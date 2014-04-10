#include "mysvm.h"
#include <vector>
#include  "feature/featuremanager.h"
#include "label/labelmanager.h"
#include "label/label.h"
#include <fstream>
#include "model/libsvm/svm.h"
#include <stdlib.h>

using namespace std;

MySVM::MySVM()
{
    baseDir = "/home/lsq/data/svm/";
    featureName = "dct.";
    imgDir = "/home/lsq/data/image/";                      //训练图像的路径
    featurePath = baseDir + featureName + "svm.feature";                                 //特征存放位置
    modelPath = baseDir + featureName + "svm.model";
    labelPath = baseDir + featureName + "svm.label";

    //-----------train parameter
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.degree = 3;
    param.gamma = 0;	// 1/num_features
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 1;
    param.eps = 1e-3;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = 0;
    param.weight = 0;

    cross_validation = 0;



    //max_line1_len;
    //model;                 // train & predict

    //----------------------predict parameter
  //  input = fopen(input_file_name.c_str(),"r");
   // output = fopen("/home/lsq/data/feature/svm/dct-svm.re","w");                        //要预测的数据
                                                                                //结果存放的位置
   //x;
    max_nr_attr = 36192;//64;
    predict_probability=0;

    line1 = 0;
//    max_line1_len;


}

MySVM:: ~MySVM(){
    //free
  //  myfree();

}


/*-------------------train---------------
        1.设定参数
        2.设定训练样本路径input_file_name，数据格式按libsvm 要求c++格式
        3.设定训练SVM结果路径 model_file_name，数据格式按libsvm 要求c++格式
        4.设置svm  param  (构造函数里有默认值)
*///---------------------------------------
void MySVM::train(){

   // myfree();
   //setTrainParameter();

   // input_file_name="/home/lsq/data/feature/svm/dct-svm.fe";  //
    //model_file_name="/home/lsq/data/feature/svm/dct-svm.model";
    const char *error_msg;
    error_msg = svm_check_parameter(&prob,&param);
    read_problem(featurePath.c_str());
    if(error_msg)
    {
        printf("ERROR: %s\n",error_msg);
       return ;
    }

    if(cross_validation)
    {
      ;//如果交叉检验;
    } else{
        model = svm_train(&prob,&param);
//      cout<< "prob.l = "<<prob.l <<endl;
//      for(int i=0;i<prob.l;i++){
//           cout<<i <<" : "<<prob.y[i]<<endl;
//      }

        if(svm_save_model(modelPath.c_str(),model))
        {
            printf( "can't save model to file %s\n", modelPath.c_str());
            return ;
        }
        svm_free_and_destroy_model(&model);
    }
    svm_destroy_param(&param);
    free(prob.y);
    free(prob.x);
    free(x_space);
    free(line1);



}

bool MySVM::classify(const string &filePath,vector<string>& labels){

    if(filePath.empty()) return false;
//    Mat img = imread(filePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//    if(!img.data) return false;
    if(predict(filePath, labels))  return true;

    return false;


}
void MySVM::myfree(){

        svm_free_and_destroy_model(&model);
        svm_destroy_param(&param);
        if(prob.y)free(prob.y);
        if(prob.x)free(prob.x);
        if(x_space)free(x_space);
        if(line1)free(line1);

}


bool MySVM::predict(const string &filePath,vector<string>& labels){
   //input=fopen("/home/lsq/data/feature/svm/dct-svm.fe","r"),
   //output=fopen("/home/lsq/data/feature/svm/dct-svm.re","w");
   //char modelPath[] = "/home/lsq/heart_scale.model";
   // Mat img = imread("/home/lsq/data/image/door/door0001.jpg",CV_LOAD_IMAGE_GRAYSCALE);

    Mat fMat;

    switch(featurType){
    case 0 :
    {
        Mat img =imread(filePath.c_str(),CV_LOAD_IMAGE_GRAYSCALE);
        Feature f;
        f.setUseBlk(true);
        f.setColorSpaceType(CST_RGB);
        FeatureManager::get()->imgDCT(img, fMat, f);
        break;
    }
    case 1 :
    {
        IplImage* pImage=cvLoadImage(filePath.c_str());
        if (!pImage->imageData){
            cout << "Error opening image:  " << endl;
           return false;
        }
        CvMat* pFeatureMat = FeatureManager::get()->getLbpSpmFeatureByImage(pImage);
        Mat tmp(pFeatureMat);
        fMat =tmp.clone();
        cvReleaseMat(&pFeatureMat);
        cvReleaseImage(&pImage);
        break;
    }
    case 2 :{
        IplImage* pImage=cvLoadImage(filePath.c_str());
        if (!pImage->imageData){
            cout << "Error opening image:  " << endl;
           return false;
        }
        CvMat* pFeatureMat = FeatureManager::get()->getLbpSpmFeatureByImage(pImage);
        Mat tmp(pFeatureMat);
        fMat =tmp.clone();
        cvReleaseMat(&pFeatureMat);
        cvReleaseImage(&pImage);
        break;
    }
    default:
       return false;
   }


    int count =0;
    max_nr_attr = fMat.rows*fMat.cols;
    struct svm_node *sn =(struct svm_node *) malloc((max_nr_attr+1)*sizeof(struct svm_node));
    for(int irow = 0; irow<fMat.rows; irow++){
        for(int icol = 0; icol<fMat.cols; icol ++){
           sn[count].index =count+1;
           sn[count].value = fMat.at<float>(irow,icol);
           count++;
            //oFeatureFile <<count <<":" <<fMat.at<float>(irow,icol)<<" ";
        }
    }
    sn[count].index = -1;
    sn[count].value =0;
cout<< count<<endl;
    if((model=svm_load_model(modelPath.c_str()))==0)
    {
        printf("can't open model file %s\n",modelPath.c_str());
        return false;
    }
    int c = svm_predict(model,sn);

    if(svmlabels.empty()) {
        if(!readLabels()){
            return false;
        }

    }
    cout << "test c= "<<svmlabels[c]<<endl;
    labels.push_back(svmlabels[c]);
    //x = (struct svm_node *) malloc(max_nr_attr*sizeof(struct svm_node));
    // predict(input,output);
    svm_free_and_destroy_model(&model);
    free(sn);

    return true;
    //free(x);
   // free(line1);
   // fclose(input);
   // fclose(output);

}


 void MySVM::read_problem(const char *filename)
 {
     int elements, max_index, inst_max_index, i, j;
     FILE *fp = fopen(filename,"r");
     char *endptr;
     char *idx, *val, *label;

     if(fp == 0)
     {
         printf("can't open input file %s\n",filename);
         return ;
     }

     prob.l = 0;
     elements = 0;

     max_line1_len = 1024;
     line1 = Malloc(char,max_line1_len);
     while(readline1(fp)!=0)
     {
         char *p = strtok(line1," \t"); // label

         // features
         while(1)
         {
             p = strtok(0," \t");
             if(p == 0 || *p == '\n') // check '\n' as ' ' may be after the last feature
                 break;
             ++elements;
         }
         ++elements;
         ++prob.l;
     }
     rewind(fp);

     prob.y = Malloc(double,prob.l);
     prob.x = Malloc(struct svm_node *,prob.l);
     x_space = Malloc(struct svm_node,elements);

     max_index = 0;
     j=0;
     for(i=0;i<prob.l;i++)
     {
         inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
         readline1(fp);
         prob.x[i] = &x_space[j];
         label = strtok(line1," \t\n");
         if(label == 0) // empty line1
           {  printf("empty line in read_problem\n");
             return ;
}
         prob.y[i] = strtod(label,&endptr);
         if(endptr == label || *endptr != '\0')
         {    printf("empty line or endptr in read_problem\n");
            return ;
}
         while(1)
         {
             idx = strtok(0,":");
             val = strtok(0," \t");

             if(val == 0)
                 break;

             int errno = 0;
             x_space[j].index = (int) strtol(idx,&endptr,10);
             if(endptr == idx || errno != 0 || *endptr != '\0' || x_space[j].index <= inst_max_index)
             {
                 printf("error in read_problem\n");
                 return;
             }
             else
                 inst_max_index = x_space[j].index;

             errno = 0;
             x_space[j].value = strtod(val,&endptr);
             if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
               {   printf("error1 in read_problem\n");
                 return;
}
             ++j;
         }

         if(inst_max_index > max_index)
             max_index = inst_max_index;
         x_space[j++].index = -1;
     }

     if(param.gamma == 0 && max_index > 0)
         param.gamma = 1.0/max_index;

     if(param.kernel_type == PRECOMPUTED)
         for(i=0;i<prob.l;i++)
         {
             if (prob.x[i][0].index != 0)
             {
                 printf("Wrong input format: first column must be 0:sample_serial_number\n");
                 return;
             }
             if ((int)prob.x[i][0].value <= 0 || (int)prob.x[i][0].value > max_index)
             {
                 printf("Wrong input format: sample_serial_number out of range\n");
                return ;
             }
         }

     fclose(fp);
 }

 void MySVM::featureExtraction()
{
     //dct-svm.fe gabor-svm.fe lbpspm-svm.fe svm.class
     //imgPath = "/home/lsq/data/image/";                      //训练图像的路径
     //featurePath = "/home/lsq/data/feature/svm/";            //特征存放位置
      vector<Label> labels = LabelManager::get();

      ofstream ofile(labelPath.c_str());
      if(!ofile) return ;
      cout << "-------------------------------------------- --"<<labels.size()<<endl;
      for(vector<Label>::size_type i = 0; i<labels.size(); i++){       //libsvm 中类别对应的整数
          svmlabels.push_back(labels[i].getName());
          ofile << setw(20) << labels[i].getName() <<"  " << i <<endl;
      }
      ofile.close();

      ofstream oFeatureFile (featurePath.c_str());
      if(!oFeatureFile) return;
    for(vector<Label>::size_type i =0; i<labels.size();i++){           //  all label

         vector<string> images = labels[i].getImages();
         for(vector<string>::size_type j =0; j < images.size(); j++){                    // each label
             string filePath= imgDir + labels[i].getName()+"/" ;
             Mat fMat;
             switch (featurType) {
                case 0: //dct
             {
                 Mat img = imread((filePath + images[j]).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
                 if (!img.data){
                     cout << "Error opening image:  " << (filePath+images[j]) << endl;
                    return ;
                 }
                 Feature f;
                 f.setUseBlk(true);
                 f.setColorSpaceType(CST_RGB);
                 FeatureManager::get()->imgDCT(img, fMat, f);
                  break;
                 }
                case 1: //lbp.spm
                 {
                     IplImage* pImage=cvLoadImage((filePath + images[j]).c_str());
                     if (!pImage->imageData){
                         cout << "Error opening image:  " << (filePath+images[j]) << endl;
                        return ;
                     }
                     CvMat* pFeatureMat = FeatureManager::get()->getLbpSpmFeatureByImage(pImage);
                     Mat tmp(pFeatureMat);
                     fMat =tmp.clone();
                     cvReleaseMat(&pFeatureMat);
                     cvReleaseImage(&pImage);

                 break;
               }
                case 2: //gabor
                 {
                     IplImage* pImage=cvLoadImage((filePath + images[j]).c_str());
                     if (!pImage->imageData){
                         cout << "Error opening image:  " << (filePath+images[j]) << endl;
                        return ;
                     }
                     CvMat* pFeatureMat = FeatureManager::get()->getGaborFeatureByImage(pImage);
                     Mat tmp(pFeatureMat);
                     fMat =tmp.clone();
                     cvReleaseMat(&pFeatureMat);
                     cvReleaseImage(&pImage);
                 break;
                }
                default:
                return ;
             }

             oFeatureFile << i << " "; //Mat=>to libsvm
             int count =0;
             for(int irow = 0; irow<fMat.rows; irow++){
                 for(int icol = 0; icol<fMat.cols; icol ++){
                     count++;
                     oFeatureFile <<count <<":" <<fMat.at<float>(irow,icol)<<" ";
                 }
             }
//             cout <<"位数"<<count << "ss"<<fMat.rows*fMat.cols<<endl;
              oFeatureFile << endl;
         }
    }
     oFeatureFile.close();
//     cout <<"ok " <<endl;
     return ;

}

void MySVM::switchFeature(){//internal test
    return ;

}
bool MySVM::setFeatureType(int t = 0){
   featurType = t;
    switch(featurType){
        case 0:
            featureName = "dct.";
            break;
        case 1:
            featureName = "lbp.spm.";
           break;
        case 2:
            featureName = "gabor.";
           break;
         default:
            featureName = "wrong.type.";
             return false;

    }
    featurePath = baseDir + featureName + "svm.feature";                                 //特征存放位置
    modelPath = baseDir + featureName + "svm.model";
    labelPath = baseDir + featureName + "svm.label";
    return true;

}
bool MySVM::readLabels(){
    if(svmlabels.empty()){
        ifstream ifile(labelPath.c_str());
        if(ifile.is_open()){
         string s;
         int i;
         while (ifile >> s ){
            svmlabels.push_back(s);
            ifile >> i;
//             cout <<s<<endl;
          }

        }

        ifile.close();
        if(!svmlabels.empty()){
          return true;
        }

    }
    return false;
}


char* MySVM::readline1(FILE *input)
    {
        int len;

        if(fgets(line1,max_line1_len,input) == 0)
            return 0;

        while(strrchr(line1,'\n') == 0)
        {
            max_line1_len *= 2;
            line1 = (char *) realloc(line1,max_line1_len);
            len = (int) strlen(line1);
            if(fgets(line1+len,max_line1_len-len,input) == 0)
                break;
        }
        return line1;
    }

void MySVM::predict(FILE *input, FILE *output)
{
    int correct = 0;
    int total = 0;
    double error = 0;
    double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

    int svm_type=svm_get_svm_type(model);
    int nr_class=svm_get_nr_class(model);
    double *prob_estimates=0;
    int j;

    if(predict_probability)
    {
        if (svm_type==NU_SVR || svm_type==EPSILON_SVR)
            printf("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n",svm_get_svr_probability(model));
        else
        {
            int *labels=(int *) malloc(nr_class*sizeof(int));
            svm_get_labels(model,labels);
            prob_estimates = (double *) malloc(nr_class*sizeof(double));
            fprintf(output,"labels");
            for(j=0;j<nr_class;j++)
                fprintf(output," %d",labels[j]);
            fprintf(output,"\n");
            free(labels);
        }
    }

    max_line1_len = 1024;
    line1 = (char *)malloc(max_line1_len*sizeof(char));
    while(readline1(input) != 0)
    {
        int i = 0;
        double target_label, predict_label;
        char *idx, *val, *label, *endptr;
        int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

        label = strtok(line1," \t\n");
        if(label == 0) // empty line1
         {   printf("error in predict_file\n");
            return;
           }
        target_label = strtod(label,&endptr);
        if(endptr == label || *endptr != '\0')
            printf("error1 in predict_file\n");
            exit(total+1);

        while(1)
        {
            if(i>=max_nr_attr-1)	// need one more for index = -1
            {
                max_nr_attr *= 2;
                x = (struct svm_node *) realloc(x,max_nr_attr*sizeof(struct svm_node));
            }

            idx = strtok(0,":");
            val = strtok(0," \t");

            if(val == 0)
                break;
            int errno = 0;
            x[i].index = (int) strtol(idx,&endptr,10);
            if(endptr == idx || errno != 0 || *endptr != '\0' || x[i].index <= inst_max_index)
             {
                printf("error2 in predict_file\n");
                return;
            }
            else
                inst_max_index = x[i].index;

            errno = 0;
            x[i].value = strtod(val,&endptr);
            if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
              {
               printf("error3 in predict_file\n");
               return;
            }

            ++i;
        }
        x[i].index = -1;

        if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
        {
            predict_label = svm_predict_probability(model,x,prob_estimates);
            fprintf(output,"%g",predict_label);
            for(j=0;j<nr_class;j++)
                fprintf(output," %g",prob_estimates[j]);
            fprintf(output,"\n");
        }
        else
        {
            predict_label = svm_predict(model,x);
            fprintf(output,"this?%g\n",predict_label);
        }

        if(predict_label == target_label)
            ++correct;
        error += (predict_label-target_label)*(predict_label-target_label);
        sump += predict_label;
        sumt += target_label;
        sumpp += predict_label*predict_label;
        sumtt += target_label*target_label;
        sumpt += predict_label*target_label;
        ++total;
    }
    if (svm_type==NU_SVR || svm_type==EPSILON_SVR)
    {
        printf("Mean squared error = %g (regression)\n",error/total);
        printf("Squared correlation coefficient = %g (regression)\n",
               ((total*sumpt-sump*sumt)*(total*sumpt-sump*sumt))/
               ((total*sumpp-sump*sump)*(total*sumtt-sumt*sumt))
               );
    }
    else
        printf("Accuracy = %g%% (%d/%d) (classification)\n",
               (double)correct/total*100,correct,total);
    if(predict_probability)
        free(prob_estimates);
}
///
void MySVM::easyDemo(){
    int train =0;
    if(train){//train
        MySVM svm;
        for(int i = 0; i<3;i++){
            svm.setFeatureType(i);
            svm.featureExtraction();
            svm.train();
        }
    }else{
        //classify()
        MySVM svm;
        for(int i = 0; i<3;i++){
            svm.setFeatureType(i);
          //  svm.featureExtraction();
           // svm.train();
            vector<string > l;
               if(svm.classify("/home/lsq/data/image/computer/monitor0003.jpg",l)){
                   cout <<i<< "---------------------------------结果------------------"<< l[0] <<endl;
               }
        }
    }
}
