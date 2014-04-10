#ifndef MBRMFEATURE_H
#define MBRMFEATURE_H

#include "feature.h"
#include "cvgabor.h"
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MBRMFeature
{
public:
    MBRMFeature();

    static MBRMFeature* instance;
    static MBRMFeature*	getInstance(){
        if(instance==NULL){
            instance=new MBRMFeature();
        }
        return instance;
    }

    static void	free(){
        if(instance!=NULL){
            delete instance;
        }
        instance=NULL;
    }

public:
    CvMat* getMbrmFeatureByImage(IplImage* pImage,int rowNumber, int colNumber);////the feature is row vector;the returned mat need to be released by user.
    CvMat* getMbrmLbpSpmFeatureByImage(IplImage* pImage,int rowNumber, int colNumber);////the feature is row vector;the returned mat need to be released by user.
    CvMat* getLbpSpmFeatureByImage(IplImage* pImage);////the feature is row vector;the returned mat need to be released by user.
    CvMat* getGaborFeatureByImage(IplImage* pImage);////the feature is row vector;the returned mat need to be released by user.
private:
    double* getGridMbrmFeature(IplImage* pImage);
    double* getGridMbrmLbpSpmFeature(IplImage* pImage);
private:
  //  bool	LVQ(const CMatDouble& inFeature,CMatDouble& outFeature);
};

#endif // MBRMFEATURE_H
