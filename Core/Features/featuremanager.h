#ifndef FEATUREMANAGER_H
#define FEATUREMANAGER_H
#include "feature.h"
#include "cvgabor.h"
#include <vector>
#include <string>
#include <list>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
class FeatureManager
{
private:
    static	FeatureManager*	instance;
public:
    FeatureManager();
    ~FeatureManager();

public:
    static FeatureManager*	getInstance(){                   //管理器 全局
        if(instance==NULL){
            instance=new FeatureManager();
        }
        return instance;
    }

    static void	free(){                               //释放
        if(instance!=NULL){
            delete instance;
        }
        instance=NULL;
    }
//:::::::::::::::::::::::::::持久化管理::::::::::::::::::::::::::::::::::::::::::::::::::
public:
    bool	addFeature(const Feature& feature);
    bool	delFeature(const string& name);
    unsigned int	getFeatureCount();
    EFeatureType	getFeatureType(const string& featureName);
    //bool	getAllFeaturef(vector<string>& featureName); //what is this?!
    bool	ifFeatureExistsByName(const string& name)const;
    bool	updateFeature(const string& name,const Feature& feature);
    bool    copyAllFeatures(std::vector<AbstractFeature> buf, const int len);
    //Copy all existing features to a new vector-buffer defined by buf.
    bool    readFeatures(const string configFileName = "config.ini");
    bool    writeFeatures(const string configFileName = "config.ini");
private:
    std::list<Feature> features;

//::::::::::::::::::::::::::::::::特征提取:::::::::::::::::::::::::::::::::::::::::::::
public:
    void imgDCT(const Mat& img, Mat& vectMat,const Feature& feature); //
    void zigZag(Mat& src, Mat& vec,int dim);//dct zigzag
    void getFeatureByImage(Mat& img,Mat& vec,const Feature& featureParam);//特征放在Mat里 featureParam为要提取的特征参数
    //Mat getFeatureByClass(const string& label,const Feature& featureParam);//Get feature according to classifier?
    //int	getFeatureNumOfClass(const string& label,const Feature& featureParam);//Get numbers of features according to classifier?
    int		getFeatureNumOfImage(const string& imageName,const Feature& feature);
    int	getMatBlkNum(const int& height,const int& width,const SBlkParameter& blkPara);
private:
    void feature(Mat& img,Mat& vec, const Feature& feature);//

};

#endif // FEATUREMANAGER_H
