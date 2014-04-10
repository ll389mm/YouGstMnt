#include "feature.h"

Feature::Feature(){
    m_featureType = FT_DCT;
    m_colorspaceType=CST_RGB;
    m_featureDim=32;
    m_usedCount=0;
    m_isUseBlk=true;
    m_blkParameter.cols = 16;
    m_blkParameter.rows = 16;
    m_blkParameter.step_cols = 8;
    m_blkParameter.step_rows = 8;

}

Feature::Feature(const string& name)
{
    Feature();
    m_name = name;
}
Feature::Feature(const Feature& feature)
{
    feature.getName(m_name);
    feature.getFeatureType(m_featureType);
    feature.getColorSpaceType(m_colorspaceType);
    m_usedCount = feature.getUsedCount();
    m_featureDim = feature.getFeatureDim();
    m_isUseBlk = feature.isUseBlk();
    //if(m_isUseBlk){
        feature.getBlkData(m_blkParameter);
   // }
}
Feature::~Feature()
{
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
bool Feature::load(const string& name)
{
   m_name = name;
    return false;
}
bool Feature::load()
{
    return false;//CDataManager::Read(*this);
}
bool Feature::save()
{
    return false;
}

