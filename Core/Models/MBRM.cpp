
#include "MBRM.h"
#include "label/label.h"
#include "label/labelmanager.h"
#include <stdlib.h>
int compare(const void* a, const void* b);
int M_compare(const void* a, const void* b);
const unsigned int N=10;
MBRM::MBRM():Model(){
    m_rowNumber=4;
    m_colNumber=6;
    m_covFactor=10000;
    m_proFactor=0;
}
MBRM::MBRM(const string& name){
	m_name=name;
	m_rowNumber=2;
	m_colNumber=3;
	m_covFactor=1900.0;
	m_proFactor=10;
}
MBRM::~MBRM(){
}

bool    MBRM::train(const string& label){  //MBRM Feature

    vector<Label> labels = LabelManager::get();
     for(int i =0; i<labels.size();i++){//  all label
         string exePath ="/home/lsq/jpg/";
         CvMat* pFeatureMat=NULL;
         CvFileStorage* fs=cvOpenFileStorage((exePath+"/"+labels[i].getName()+".xml").c_str(),0,CV_STORAGE_WRITE);
         cvWriteInt(fs,"count",labels[i].getCount());

         vector<string> images = labels[i].getImages();
         for(int j =0; j < images.size(); j++){ // each label
             string filePath= exePath + labels[i].getName()+"/" ;

             IplImage* pImage=cvLoadImage((filePath + images[j]).c_str());
             if (!pImage){
                 cout << "Error opening image:  " << (filePath+images[j]) << endl;
             }
             pFeatureMat=FeatureManager::get()->getMbrmFeatureByImage(pImage, this->getRowNumber(), this->getColNumber());


              std::stringstream ss;
              std::string str;
              ss<<j;
              ss>>str;


             cvWrite(fs,(labels[i].getName()+str).c_str(), pFeatureMat);
             cvReleaseMat(&pFeatureMat);
             cvReleaseImage(&pImage);
         }
      cvReleaseFileStorage(&fs);
    }
     return true;

}

bool MBRM::classify(IplImage*	pImage,vector<string>& labels){  //MBRM Model


	//get features of the test image
    CvMat* pFeatureMatTest=cvCreateMat(this->getRowNumber()*this->getColNumber(),MBRMDIM,CV_64FC1);
    pFeatureMatTest=FeatureManager::get()->getMbrmFeatureByImage(pImage,this->getRowNumber(),this->getColNumber());

    //CArrayString allLabels;//all labels in the training set
    //CLabelManager::Get()->GetAllLabels(allLabels);//get all labels

  vector<Label> allLabels = LabelManager::get();
    int labelsCount=LabelManager::getlblsCount();


	SMLabelprblty* result = new SMLabelprblty[labelsCount];
Label l;
	for(int i=0; i!=labelsCount; ++i)
	{
        result[i].label=allLabels[i].getName();
		result[i].probability = M_PossibilityOfLabel(pFeatureMatTest, result[i].label);
	}
	cvReleaseMat(&pFeatureMatTest);
	qsort(result,labelsCount,sizeof(SMLabelprblty),M_compare);
/***********************************************************/



	for (int i=0; i!=2;++i)
	{
        labels.push_back(result[i].label);
	}
	return true;
}

double	MBRM::possibilityOfLabel(CvMat* pFeatureMatTest, const string& label/*, CArrayString& allLabels*/)
{
	double posblty=0.0;
	int imgCount;

	CvMat* pFeaturesMatJ=NULL;

	

    string exePath ="/home/lsq/jpg/";
    string path = exePath+"/" + label +".xml";
	CvFileStorage* fs=cvOpenFileStorage(path.c_str(), 0, CV_STORAGE_READ);
	if(!fs){
        cout<<(path.c_str())<<endl;
	}
	imgCount = cvReadIntByName(fs, 0, "count");
	char iStr[N];

	for (int i=0; i!=imgCount; ++i)
	{

        std::stringstream ss;
        std::string str;
        ss<<i;
        ss>>str;

        pFeaturesMatJ = (CvMat*)cvReadByName(fs,0,(label+str).c_str());
		posblty += PGJ(pFeatureMatTest, pFeaturesMatJ);
		cvReleaseMat(&pFeaturesMatJ);
	}
	cvReleaseFileStorage(&fs);

	return posblty;
}

MyRealNo MBRM::M_PossibilityOfLabel(CvMat* pFeatureMatTest, const string& label/*, double beta*/)
{
	//	double posblty=0.0;
	MyRealNo poss(0.0);
	int imgCount;
	int nRegionTest=pFeatureMatTest->rows;


     string exePath ="/home/lsq/jpg/";
    string datapath = exePath+"/" + label +".xml";
    CvFileStorage* fs=cvOpenFileStorage((exePath+"/" + label +".xml").c_str(), 0, CV_STORAGE_READ);

	imgCount = cvReadIntByName(fs, 0, "count");


	CvMat* pFeatureVecTest=cvCreateMat(1,MBRMDIM,CV_64FC1);
	cvReleaseData(pFeatureVecTest);





	for (int i=0; i!=imgCount; ++i)
	{
		MyRealNo prod(1.0);
		//		double temp=1.0;


        std::stringstream ss;
        std::string str;
        ss<<i;
        ss>>str;

        CvMat* pFeaturesMatJ = (CvMat*)cvReadByName(fs,0,(label+str).c_str());
		if(!pFeaturesMatJ)
            cout << "Error reading item" << (label+str) << endl;
		for (int row=0; row!=nRegionTest; ++row)
		{
			cvGetRow(pFeatureMatTest, pFeatureVecTest, row);
			//time_t start=time(0);
			double pgj_temp=M_PGJ(pFeatureVecTest,pFeaturesMatJ/*,beta*/);
			//cout << "PGJ" <<time(0)-start <<"s ";
			MyRealNo tempMR(pgj_temp);
			prod.multiply(tempMR);
			//			temp *= pgj_temp;
			cvReleaseData(pFeatureVecTest);
		}
		//		posblty += temp;
		if (0==i)
			poss=prod;
		else
			poss.add(prod);

		cvReleaseMat(&pFeaturesMatJ);
	}
	//	posblty /= imgCount;
	cvReleaseFileStorage(&fs);
	//	return posblty;
	poss.devide(imgCount);
	return poss;
}

double MBRM::PGJ(CvMat* pFeatureMatTest, CvMat* pFeaturesMatJ/*, double beta*/)
{
    double beta=this->getCovFactor();
	double psbltyGJ=0.0;
	int dimTest=pFeatureMatTest->cols;
	int nRegionsTest=pFeatureMatTest->rows;
	int dimJ=pFeaturesMatJ->cols;//ά
	int nRegionsJ=pFeaturesMatJ->rows;//JֳɵĿ
	
	CvMat* pRectFeatureJ=cvCreateMat(1,MBRMDIM,CV_64FC1);
	cvReleaseData(pRectFeatureJ);
	CvMat* pRectFeatureTest=cvCreateMat(1,MBRMDIM,CV_64FC1);
	cvReleaseData(pRectFeatureTest);
	double product;

	CvMat* subResult=cvCreateMat(1,pFeaturesMatJ->cols,CV_64FC1);//

	for(int rowTest=0; rowTest!=pFeatureMatTest->rows; ++rowTest)
	{
		double psbltyGJtemp=0.0;
		pRectFeatureTest=cvGetRow(pFeatureMatTest,pRectFeatureTest,rowTest);
		for (int row=0; row!=pFeaturesMatJ->rows;++row)
		{
			
			pRectFeatureJ=cvGetRow(pFeaturesMatJ,pRectFeatureJ,row);//ȡ
			cvSub(pRectFeatureTest,pRectFeatureJ,subResult);//
			product=cvDotProduct(subResult,subResult);
			psbltyGJtemp+=pow(MY_E,-product/beta);
			cvReleaseData(pRectFeatureJ);
			

		}
		
		psbltyGJtemp/=nRegionsJ;
		psbltyGJ+=psbltyGJtemp;

	}
	cvReleaseMat(&subResult);
	cvReleaseMat(&pRectFeatureJ);
	cvReleaseMat(&pRectFeatureTest);
	psbltyGJ/=nRegionsTest;	
	return psbltyGJ;	
}

double MBRM::M_PGJ(CvMat* pFeatureVecTest, CvMat* pFeaturesMatJ/*, double beta*/)
{
	double psbltyGJ=0.0;

	int nRegionsJ=pFeaturesMatJ->rows;//JֳɵĿ


	CvMat* pRectFeatureJ=cvCreateMat(1,MBRMDIM,CV_64FC1);
	cvReleaseData(pRectFeatureJ);
	double product;

	CvMat* subResult=cvCreateMat(1,MBRMDIM,CV_64FC1);

	for (int row=0; row!=nRegionsJ;++row)
	{

		
		cvGetRow(pFeaturesMatJ,pRectFeatureJ,row);//ȡ
		cvSub(pFeatureVecTest,pRectFeatureJ,subResult,0);//
		product=cvDotProduct(subResult,subResult);
        double temp=exp(-product/this->getCovFactor());/*pow(MY_E,-product/beta);*/
		psbltyGJ+=temp;

		
	}
	cvReleaseMat(&subResult);
	psbltyGJ/=nRegionsJ;
	cvReleaseMat(&pRectFeatureJ);
	return psbltyGJ;	
}
int compare(const void* a, const void* b)
{
	PSLabelPrblty pS1,pS2;
	pS1=(PSLabelPrblty)a;
	pS2=(PSLabelPrblty)b;
	if(pS1->probability < pS2->probability)
		return -1;
	else if(pS1->probability==pS2->probability)
		return 0;
	else
		return 1;
}
int M_compare(const void* a, const void* b)
{
	PSMLabelprblty pS1,pS2;
	pS1=(PSMLabelprblty)a;
	pS2=(PSMLabelprblty)b;
	if(pS1->probability.getE() < pS2->probability.getE())
		return 1;
	else if(pS1->probability.getE()==pS2->probability.getE() && pS1->probability.getM()==pS2->probability.getM())
		return 0;
	else
		return -1;
}

/*bool MBRM::myTest()
{
    //CArrayString labels;
vector<string> labels;


	IplImage* pImg = cvLoadImage("d:\\test.jpg");

        MBRM::classify(pImg,labels);

		cvReleaseImage(&pImg);

	return true;

}*/
