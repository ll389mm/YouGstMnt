#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <vector>
#include <string>
using namespace std;

enum	EColorSpaceType{
    CST_UNKNOWN=-1,
    CST_RGB=0,
    CST_HSV,
    CST_HLS,
    CST_LUV,
    CST_YBR
};
#define CST_NUM	5//颜色特征空间数目ColorSpaceType
class ColorSpace
{
public:
    ColorSpace();
    ~ColorSpace();

public:
    static	bool	getAllColorSpaceType(vector<string>& ColorSpaceType);
    static	bool	getAllColorSpaceType(vector<int>&	ColorSpaceType);
public:
    static	string	getColorSpaceType(const EColorSpaceType& eColorSpaceType);
    static	EColorSpaceType	getColorSpaceType(const string& sColorSpaceType);
public:
    static bool	isValid(const string& sColorSpaceType);
    static bool	isValid(const EColorSpaceType& eColorSpaceType);
private:
    static	EColorSpaceType	m_intColorSpaceType[CST_NUM];//数字型的
    static	vector<string>		m_strColorSpaceType;//字符串型的
};

#endif // COLORSPACE_H
