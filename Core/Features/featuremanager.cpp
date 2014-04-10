#include "featuremanager.h"
#include "SPM.h"
#include "LBP.h"

//Initialize and management
FeatureManager*	FeatureManager::instance=NULL;
FeatureManager::FeatureManager()
{}
FeatureManager::~FeatureManager()
{}


//...........................................................
//Preservation management
bool FeatureManager::ifFeatureExistsByName(const std::string &name) {
    std::list<Feature>::iterator it(features.begin());
    while (it != features.end()) {
        if (name == it->getName()) return true; ++it;
    } return false;
}

bool	FeatureManager::addFeature(const Feature& feature)
{
    if (ifFeatureExistsByName(feature->getName())) return false;
    features.insert(features.end(), *feature);
    return true;
}
bool	FeatureManager::delFeature(const string& name)
{
    std::list<Feature>::iterator it(features.begin());
    while (it != features.end()) {
        if (name == it->getName()) {
            features.erase(it); return true;
        } ++it;
    } return false;
}
unsigned int	FeatureManager::getFeatureCount()
{
    return features.size();
}
EFeatureType	FeatureManager::getFeatureType(const string& featureName)
{
    //to be done as follows:
    //Follow features and compare names.
}
/*bool	FeatureManager::getAllFeature(CArrayString& featureDefName)
{
    return (CDataManager::GetAllFeatureDef(featureDefName)!=INT_ERROR_CODE);
}*/ //what is this ? remove after verification.
/*bool	FeatureManager::IsFeatureDefExists(const _tstring& name)const
{
    return CDataManager::IsFeatureDefExists(name);
}*/ //remove after verifing that no other function uses it.
bool	FeatureManager::UpdateFeatureDef(const _tstring& name,const Feature& featureDef)
{
    if(!DelFeatureDef(name))
        return false;
    if(!AddFeatureDef(featureDef))
        return false;
    return true;
}
bool FeatureManager::copyAllFeatures(std::vector<AbstractFeature> buf, const int len) {
    if (len < 1) return 0;
    std::list<Feature>::const_iterator it(features.begin());
    int n = 0;
    while (it != features.end() && n < len) {
        buf[n] = *it; ++it; ++n;
    }
    return n;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
int	FeatureManager::getMatBlkNum(const int& height,const int& width,const SBlkParameter& blkPara){
    if(height<blkPara.rows||width<blkPara.cols)
        return 0;
    unsigned int rbn=static_cast<unsigned int>(ceil((double)(height-blkPara.rows)/blkPara.step_rows))+1;
    unsigned int cbn=static_cast<unsigned int>(ceil((double)(width-blkPara.cols)/blkPara.step_cols))+1;
    return static_cast<int>(rbn*cbn);//特征向量的数目
}
int	FeatureManager::getFeatureNumOfImage(const string& imageName,const Feature& feature)
{
    int		featureNum=0;
    Mat img = imread(imageName);
    if(img.data){
        if(!feature.isUseBlk()){
            featureNum=1;
        }else{
            SBlkParameter blkPara;

            if(feature.getBlkData(blkPara)){
                featureNum= getMatBlkNum(img.rows,img.cols,blkPara);
            }
        }
    }
    return featureNum;
}
void FeatureManager::zigZag(Mat& src, Mat& vec,int dim){
/*::::::::::::::::::::::::::::::::::::dct zigzag
    vec.rows == src.rows*src.cols , vec.cols == dim; &&
    src.rows == src.cols == 2*n;                     &&
    dim <=rows*cols
::::::::::::::::::::::::::::::::::::*/
    int count=0;
    for(int i = 0 ; i<src.cols; i++){
        for(int j= 0; j<= i ; j++){
            if(count > dim -1){
                return ;
            }
            if(i%2 == 0){
                vec.at<float>(0,count) = (src.at<float>(i-j ,j));
            }else{
                vec.at<float>(0,count) = (src.at<float>(j, i-j));
             //vec.push_back(src.at<float>(j, i-j));
            }
            count++;
        }
    }

    for(int i = 1 ; i<src.cols; i++){
        for(int j= src.cols-1 ; j>= i; j -- ){
            if(count > dim -1){
                return ;
            }
            if(i%2 == 0){
                vec.at<float>(0,count) =src.at<float>(src.rows-1 - j +i ,j);
               // vec.push_back(src.at<float>(src.rows-1 - j +i ,j));
            }else{
                vec.at<float>(0,count) = src.at<float>(j, src.cols-1 -j +i);
                //vec.push_back(src.at<float>(j, src.cols-1 -j +i));
            }
            count++;

        }
    }
    return ;
}


void FeatureManager::imgDCT(const Mat& img, Mat& vectMat,const Feature& feature) {
    /*::::::::::::::::::::::::::::::::::::
      n通道
      Mat vectMat(xblock*yblock,dim*img.channels(),CV_32FC1);//特征
    ::::::::::::::::::::::::::::::::::::*/

   // Mat img1 =imread("/home/lsq/image/lena.jpg");//,CV_LOAD_IMAGE_GRAYSCALE);
    SBlkParameter blkpara;
    feature.getBlkData(blkpara);
    int x=blkpara.cols,y=blkpara.rows,xstep = blkpara.step_cols,ystep =blkpara.step_rows ,dim =feature.getFeatureDim();

    vector<Mat> bgr;//bgr 或其他分量
    if(img.channels()==1){//单通道
        bgr.push_back(img);
    }else{ //多通道
        split(img, bgr);
    };
    int xblock = ( bgr[0].cols-x )/xstep+1;
    int yblock = (bgr[0].rows -y )/ystep +1;
  vectMat.create(xblock*yblock,dim*img.channels(),CV_32FC1);//特征
    for(int i =0; i<bgr.size(); i++){//bgr
        bgr[i] = Mat_<float>(bgr[i]);//dct数据要求
        for(int m =0; m <(bgr[i].cols-x )/xstep+1; m++ ){//cols
            for(int n=0; n<(bgr[i].rows -y )/ystep +1; n++){//rows

                Mat roi(bgr[i],Rect(m*xstep, n*ystep, xstep ,ystep));
                Mat dctMat;
                dct(roi,dctMat);                                  //块roi

                Mat roiVect(vectMat,Rect(i*dim,n*((bgr[i].cols-x )/xstep+1)+ m,dim,1));//特征roi
                zigZag(dctMat,roiVect,dim);

           }//rows
        }//cols
    }//bgr

}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void	FeatureManager::getFeatureByImage(Mat& img, Mat& vec, const Feature& feature){//
    EColorSpaceType	cst;
    feature.getColorSpaceType(cst);
    Mat src;

    switch(cst){
    case CST_RGB:
        src=img.clone();
        break;
    case CST_HSV:
        cvtColor(img, src ,CV_BGR2HSV);
        break;
    case CST_HLS:
        cvtColor(img, src, CV_BGR2HLS);
        break;
    case CST_LUV:
        cvtColor(img, src, CV_BGR2Luv);
        break;
    case CST_YBR:
        cvtColor(img, src, CV_BGR2YCrCb);
        break;
    default:

        return ;
    }

    if(feature.isUseBlk()==true){
        this->feature(src, vec, feature);
    }else{
       SBlkParameter singleBlk;
        singleBlk.cols= src.cols;
        singleBlk.rows =src.rows;
        singleBlk.step_cols=10;//非0
        singleBlk.step_rows=10;//
        Feature f(feature);
        f.setBlkData(singleBlk);

       this->feature(src, vec, f);
    }


    return ;
}
//............................................................................................................................//
void	FeatureManager::feature(Mat& img,Mat& vec,const Feature& feature)
{
    unsigned int	dim=feature.getFeatureDim();
    EFeatureType	featureType;
    feature.getFeatureType(featureType);



    switch(featureType){
        case FT_DCT:
            imgDCT(img, vec ,feature);
            break;
        case FT_DWT:
            //::cvDWT(pChannel1,pChannel2,1);
           // cvScale(pChannel2,pSrcMat);
            break;
        case FT_GABOR:
            break;
        case FT_COLORHIST:
//			::cvCalcHist(,,0,NULL);
            break;
        case FT_HIST_DCT:
            break;
        default:
            break;
    }
    return ;
}


