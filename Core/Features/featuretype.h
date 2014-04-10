#ifndef FEATURETYPE_H
#define FEATURETYPE_H
//FeatureType is a assisstantal class that defines features.
#include <string>
#include <vector>
using namespace std;

enum	EFeatureType{
    FT_UNKNOWN=-1,
    FT_COLORHIST=0,
    FT_DCT,
    FT_DWT,
    FT_GABOR,
    FT_HIST_DCT,
    FT_MBRM
};
#define	FT_NUM 6

class FeatureType
{
public:
    FeatureType();
   ~FeatureType();
public:
        static	void	getAllFeatureType(vector<string>& featureType);
        static	void	getAllFeatureType(vector<int>&	featureType);
public:
        static	string	getFeatureType(const EFeatureType& eFeatureType);
        static	EFeatureType	getFeatureType(const string& sFeatureType);
public:
        static bool	isValid(const string& sFeatureType);
        static bool	isValid(const EFeatureType& eFeatureType);
private:
        static EFeatureType m_enuFeatureType[FT_NUM];
        static vector<string> m_strFeatureType;
};

#endif // FEATURETYPE_H
