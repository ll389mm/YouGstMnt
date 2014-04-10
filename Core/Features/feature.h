#ifndef FEATURE_H
#define FEATURE_H
#include <string>
#include "colorspace.h"
#include "featuretype.h"

using namespace std;

typedef	struct _blkpara{  //结构体 分块的参数
     int rows;
     int cols;
     int step_rows;
     int step_cols;
}SBlkParameter;
  #define BLK_PCOUNT sizeof(SBlkParameter)
class Feature
{
protected:
    string              m_name;                //名称
    EFeatureType		m_featureType;         //特征类型
    EColorSpaceType		m_colorspaceType;      //用的颜色空间
    int                 m_featureDim;          //特征的维度
    int                 m_usedCount;           //统计使用次数
    bool				m_isUseBlk;            //是否用分块
    SBlkParameter		m_blkParameter;
    public:
        Feature();
        Feature(const string& name);
        Feature(const Feature& feature);
        ~Feature();
    public:
        inline bool hasName()const
        {
            return !m_name.empty();
        }
        inline bool isValid()const
        {
            if(m_name.empty()||!FeatureType::isValid(m_featureType)||!ColorSpace::isValid(m_colorspaceType)||m_featureDim==0)
                return false;
            return true;
        }
        //............................................................................
        inline bool getName( string& featureName)const
        {
            if(m_name.empty())
                return false;
            else
                featureName=m_name;
            return true;
        }
        inline bool isSameAs(const string& featureName)const
        {
            return (featureName == m_name);
        }
        inline void setName(const string featureName)
        {
            m_name=featureName;
        }
        //...........................................................................
        inline bool getColorSpaceType(EColorSpaceType& clrspaceType)const
        {
            if(ColorSpace::isValid(m_colorspaceType))
                clrspaceType=m_colorspaceType;
            else
                return false;
            return true;
        }
        inline bool isColorSpaceType(EColorSpaceType colorspace)const
        {
            return (m_colorspaceType==colorspace);
        }
        inline void setColorSpaceType(EColorSpaceType clrspaceType)
        {
            m_colorspaceType=clrspaceType;
        }
        //...............................................................
        inline  int	getFeatureDim()const
        {
            return m_featureDim;
        }
        inline void setFeatureDim( int featureDim)
        {
            m_featureDim=featureDim;
        }
        //................................................................
        inline bool getFeatureType(EFeatureType& featureType)const
        {
                featureType=m_featureType;
                return true;
        }
        inline bool isFeatureType(EFeatureType featureType)const
        {
            return (m_featureType==featureType);
        }
        inline void setFeatureType(EFeatureType featureType)
        {
            if(FeatureType::isValid(featureType))
                m_featureType=featureType;
            else
                m_featureType=FT_UNKNOWN;
        }
        //..............................................................
        inline bool isUseBlk()const
        {
            return m_isUseBlk;
        }
        inline void setUseBlk(bool isUseBlk)
        {
            m_isUseBlk=isUseBlk;
        }
        inline bool getBlkData(SBlkParameter& para)const
        {
            if(m_isUseBlk==false){
                return false;
            }
            para=m_blkParameter;
            return true;
        }
        inline bool setBlkData(const SBlkParameter& para)
        {
    //		::memcpy(&m_blkParameter,&para,sizeof(int)*BLK_PCOUNT);
            m_blkParameter=para;
            return true;
        }
        //..................................................................
        inline int	 getUsedCount()const
        {
            return m_usedCount;
        }
        inline void setUsedCount( int count)
        {
            m_usedCount=count;
        }
        inline void incUsedCount()
        {
            m_usedCount++;
        }
        inline void decUsedCount()
        {
            if(m_usedCount>0)
                m_usedCount--;
        }
        inline Feature& operator=(const Feature &t){
            t.getBlkData(this->m_blkParameter);
            this->m_usedCount= t.getUsedCount();

            t.getName(this->m_name);
            t.getColorSpaceType(this->m_colorspaceType);
            this->m_featureDim=t.getFeatureDim();
            t.getFeatureType(this->m_featureType);
            if(t.isUseBlk()){
                this->m_isUseBlk = true;
            }else{
                this->m_isUseBlk = false;

            }

            return *this;
        }
    public:
        bool			load(const string& name);
        bool			load();
        bool			save();

};


#endif // FEATURE_H
