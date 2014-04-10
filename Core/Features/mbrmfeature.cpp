#include "mbrmfeature.h"

MBRMFeature::MBRMFeature()
{
}

CvMat* FeatureManager::getMbrmFeatureByImage(IplImage* pImage, int rowNumber, int colNumber)//the feature is row vector;the returned mat need to be released by user.
{
    const int MBRMDIM=17;
    int x=0,y=0;//
    int rectWidth=pImage->width/colNumber;
    int rectHeight=pImage->height/rowNumber;
    double* pFeature=new double[rowNumber*colNumber*MBRMDIM];
    CvRect roi=cvRect(x, y, rectWidth, rectHeight);

    for (int row=0; row!=rowNumber; ++row)
    {

        for (int col=0; col!=colNumber; ++col)
        {
            IplImage*	pGridImage=::cvCreateImage(cvSize(roi.width,roi.height),pImage->depth,pImage->nChannels);

            roi.x=col*rectWidth;
            roi.y=row*rectHeight;
           // cvGetSubImage(pImage, pGridImage, roi);


            cvSetImageROI(pImage,roi);
            //	result=cvCreateImage(cvSize(roi.width,roi.height),image->depth,image->nChannels);
            cvCopy(pImage,pGridImage);
            cvResetImageROI(pImage);

            double* pGridFeature=getGridMbrmFeature(pGridImage);

            for (int i=0;i!=MBRMDIM;++i)
            {
                pFeature[MBRMDIM*(row*colNumber+col)+i]=pGridFeature[i];
            }
            delete [] pGridFeature;
            cvReleaseImage(&pGridImage);
        }

    }
    CvMat tmp = cvMat(rowNumber*colNumber,MBRMDIM,CV_64FC1,pFeature);
    CvMat* pFeatureMat=cvCreateMat(rowNumber*colNumber,MBRMDIM,CV_64FC1);
    cvCopy(&tmp,pFeatureMat);
    delete [] pFeature;
    return pFeatureMat;
}
CvMat* FeatureManager::getMbrmLbpSpmFeatureByImage(IplImage* pImage, int rowNumber, int colNumber)//the feature is row vector;the returned mat need to be released by user.
{
    IplImage* pGray = cvCreateImage(cvGetSize(pImage),8,1);//get the gray image
    cvCvtColor(pImage,pGray,CV_RGB2GRAY);

    LBP lbp;

    int pyramid[2] = {1, 2};
    SPM spm;

    // LBP
    int height, width;
    int **result = NULL;
    lbp.lbp_result(pGray->imageData, pGray->height, pGray->width, result, 0, height, width);

    //SPM
    spm.getSPM(height, width, 256, 2, pyramid, result);

    const int MBRMDIM=1280;

    CvMat tmp = cvMat(1,MBRMDIM,CV_64FC1,spm.spmData);
    CvMat* pFeatureMat=cvCreateMat(1,MBRMDIM,CV_64FC1);
    cvCopy(&tmp,pFeatureMat);
    delete [] spm.spmData;
    return pFeatureMat;
}

CvMat* FeatureManager::getLbpSpmFeatureByImage(IplImage* pImage)//the feature is row vector;the returned mat need to be released by user.
{
    IplImage* pGray = cvCreateImage(cvGetSize(pImage),8,1);//get the gray image
    cvCvtColor(pImage,pGray,CV_RGB2GRAY);

    LBP lbp;

    int pyramid[2] = {1, 2};
    SPM spm;

    Mat img(pGray);////////////////////////
    Mat img2 = img.clone();
    // LBP
    int height, width;
    int **result = NULL;
    lbp.lbp_result(pGray->imageData, pGray->height, pGray->width, result, 0, height, width);

    //SPM
    spm.getSPM(height, width, 256, 2, pyramid, result);

    const int MBRMDIM=1280;

    CvMat tmp = cvMat(1,MBRMDIM,CV_64FC1,spm.spmData);
    CvMat* pFeatureMat=cvCreateMat(1,MBRMDIM,CV_64FC1);
    cvCopy(&tmp,pFeatureMat);
    delete [] spm.spmData;
    return pFeatureMat;
}

CvMat* FeatureManager::getGaborFeatureByImage(IplImage* pImage)//the feature is row vector;the returned mat need to be released by user.
{
    double* pGridFeature=getGridMbrmFeature(pImage);

    const int MBRMDIM=1280;

    CvMat tmp = cvMat(1,MBRMDIM,CV_64FC1,pGridFeature);
    CvMat* pFeatureMat=cvCreateMat(1,MBRMDIM,CV_64FC1);
    cvCopy(&tmp,pFeatureMat);
    delete [] pGridFeature;
    return pFeatureMat;
}

double* FeatureManager::getGridMbrmFeature(IplImage* pImage)//\B6\D4һ\B8\F6\CD\F8\B8\F1\C4ڵ\C4ͼ\CF\F1\C7\F8\D3\F2\C7\F3\CC\D8\D5\F7
{
    const int MBRMDIM=17;
    double* pGridFeature=new double[MBRMDIM];//store 9 color features and 12 texture featuers
    //store 9 color moments and 12 texture features
    double bSum=0.0,gSum=0.0,rSum=0.0;

    IplImage* pGray = cvCreateImage(cvGetSize(pImage),8,1);//get the gray image
    cvCvtColor(pImage,pGray,CV_RGB2GRAY);

    //get means, standard deviation
    CvScalar rectAvg,rectSdv;
    cvAvgSdv(pImage,&rectAvg,&rectSdv);
    pGridFeature[0]=rectAvg.val[0];//B average
    pGridFeature[1]=rectAvg.val[1];//G average
    pGridFeature[2]=rectAvg.val[2];//R average
    pGridFeature[3]=rectSdv.val[0];//B Standard deviation
    pGridFeature[4]=rectSdv.val[1];//G Standard deviation
    pGridFeature[5]=rectSdv.val[2];//R Standard deviation

    //get skewness
    for(int row=0;row!=pImage->height;++row)
    {
        uchar* ptr=(uchar*)(pImage->imageData+row*pImage->widthStep);
        for(int col=0;col!=pImage->width;++col)
        {
            bSum+=pow(*(ptr+col*3)-rectAvg.val[0],3);
            gSum+=pow(*(ptr+col*3+1)-rectAvg.val[1],3);
            rSum+=pow(*(ptr+col*3+2)-rectAvg.val[2],3);
        }
    }
    pGridFeature[6]=bSum<0?-pow(1.0/(pImage->width*pImage->height)*(-bSum),1.0/3.0):pow(1.0/(pImage->width*pImage->height)*bSum,1.0/3.0);//B Skewness
    pGridFeature[7]=gSum<0?-pow(1.0/(pImage->width*pImage->height)*(-gSum),1.0/3.0):pow(1.0/(pImage->width*pImage->height)*gSum,1.0/3.0);//G Skewness
    pGridFeature[8]=rSum<0?-pow(1.0/(pImage->width*pImage->height)*(-rSum),1.0/3.0):pow(1.0/(pImage->width*pImage->height)*rSum,1.0/3.0);//R Skewness
    //get Gabor texture feature
    //\C9\FA\B3\C9һ\B8\F6Gabor\BA\CB
    CvScalar rectGaborAvg;
//	CvScalar rectGaborSdv;
    double Sigma = 2*PI;
    double F = sqrt(2.0);
    int cnt=0;
    CvGabor* gabor1=NULL;
    for(int scale =3;scale<=6;scale+=3)
        for (int orientation=0;orientation!=4;++orientation)
        {
            gabor1 = new CvGabor;
            IplImage* reimg = cvCreateImage(cvGetSize(pGray), IPL_DEPTH_8U, 1);
            gabor1->Init(PI*orientation/4,/* scale*/3, Sigma, F);
            gabor1->conv_img(pGray, reimg, CV_GABOR_REAL);
// 			cvAvgSdv(reimg,&rectGaborAvg,&rectGaborSdv);
            rectGaborAvg=cvAvg(reimg);
            cvReleaseImage(&reimg);
            pGridFeature[cnt+9]=rectGaborAvg.val[0];
            ++cnt;
//			pGridFeature[cnt+12]=rectGaborSdv.val[0];
            delete gabor1;
        }

        cvReleaseImage(&pGray);
        return pGridFeature;
}

double* FeatureManager::getGridMbrmLbpSpmFeature(IplImage* pImage)//\B6\D4һ\B8\F6\CD\F8\B8\F1\C4ڵ\C4ͼ\CF\F1\C7\F8\D3\F2\C7\F3\CC\D8\D5\F7
{
    IplImage* pGray = cvCreateImage(cvGetSize(pImage),8,1);//get the gray image
    cvCvtColor(pImage,pGray,CV_RGB2GRAY);

    LBP lbp;

    int pyramid[2] = {1, 2};
    SPM spm;

    // LBP
    int height, width;
    int **result = NULL;
    lbp.lbp_result(pGray->imageData, pGray->height, pGray->width, result, 0, height, width);

    //SPM
    spm.getSPM(height, width, 256, 2, pyramid, result);

    return spm.spmData;
}
