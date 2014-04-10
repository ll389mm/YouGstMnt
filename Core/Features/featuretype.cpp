#include "featuretype.h"

 EFeatureType FeatureType::m_enuFeatureType[FT_NUM] = {
        FT_COLORHIST,
        FT_DCT,
        FT_DWT,
        FT_GABOR,
        FT_HIST_DCT
};
 string s[]= {
     "Color Histogram",
     "DCT",
     "DWT",
     "Gabor",
     "Color Hist-DCT"
};
 vector<string> FeatureType::m_strFeatureType(s, s+5);

FeatureType::FeatureType(){}
FeatureType::~FeatureType(){}
void	FeatureType::getAllFeatureType(vector<string>& featureType){
    featureType = m_strFeatureType;
};
void	FeatureType::getAllFeatureType(vector<int>&	featureType){
    for(int i=0; i<FT_NUM; i++){
        featureType.push_back(m_enuFeatureType[i]);
    }
};
string FeatureType::getFeatureType(const EFeatureType& eFeatureType){
    string s ="";
    for(int i = 0; i<FT_NUM; i++){
        if(eFeatureType == m_enuFeatureType[i]){
            s = m_strFeatureType[i];
            break;
        }
    }
    return s;
};
EFeatureType	FeatureType::getFeatureType(const string& sFeatureType){
    EFeatureType eft = FT_UNKNOWN;
    for(int i = 0; i<m_strFeatureType.size(); i++){
        if(sFeatureType == m_strFeatureType[i]){
            eft = m_enuFeatureType[i];
            break;
        }
    }
    return eft;
};
bool	FeatureType::isValid(const string& sFeatureType){
    for(int i=0; i < m_strFeatureType.size(); i++){
        if(sFeatureType == m_strFeatureType[i])
            return true;
    }
    return false;
};
bool	FeatureType::isValid(const EFeatureType& eFeatureType){
    for(int i=0; i < FT_NUM; i++){
        if(eFeatureType == m_enuFeatureType[i])
            return true;
    }
    return false;
};

