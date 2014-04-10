#include "colorspace.h"

ColorSpace::ColorSpace()
{
}
ColorSpace::~ColorSpace()
{
}
EColorSpaceType	ColorSpace::m_intColorSpaceType[CST_NUM]={
        CST_RGB,
        CST_HSV,
        CST_HLS,
        CST_LUV,
        CST_YBR
};
string str[5] ={
        "RGB",
        "HSV",
        "HLS",
        "LUV",
        "YBR"
};
vector<string> ColorSpace:: m_strColorSpaceType(str,str+5);

bool	ColorSpace::getAllColorSpaceType(vector<string>& ColorSpaceType){
            ColorSpaceType.clear();
            if(CST_NUM<=0)
                return false;
            for(int i=0;i<CST_NUM;i++){
                ColorSpaceType.push_back(m_strColorSpaceType[i]);
             }
             return true;
};

bool	ColorSpace::getAllColorSpaceType(vector<int>&	ColorSpaceType){
            ColorSpaceType.clear();
            if(CST_NUM<=0)
                return false;
            for(int i=0;i<CST_NUM;i++){
                ColorSpaceType.push_back(m_intColorSpaceType[i]);
             }
             return true;
};

string	ColorSpace::getColorSpaceType(const EColorSpaceType& eColorSpaceType){
    string s = "";
    for(string::size_type i=0; i<CST_NUM; i++){
        if(m_intColorSpaceType[i] == eColorSpaceType){
            s = m_strColorSpaceType[i];
            return s;
        }
    }
    return s;
};
EColorSpaceType	ColorSpace::getColorSpaceType(const string& sColorSpaceType){
    EColorSpaceType	eColorSpaceType=CST_UNKNOWN;
        for(int i=0;i<CST_NUM;i++){
            if(sColorSpaceType==m_strColorSpaceType[i]){
                eColorSpaceType=m_intColorSpaceType[i];
                break;
            }
        }
        return eColorSpaceType;
};

bool	ColorSpace::isValid(const string& sColorSpaceType){
    for(int i= 0; i< CST_NUM; i++){
        if(sColorSpaceType == m_strColorSpaceType[i]){
            return true;
        }
    }//for
    return false;
};
bool	ColorSpace::isValid(const EColorSpaceType& eColorSpaceType){
    for(int i=0; i<CST_NUM; i++){
        if(eColorSpaceType == m_intColorSpaceType[i]){
            return true;
        }
    }//for
    return false;
};


