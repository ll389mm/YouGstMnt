#ifndef MRBM_H
#define MRBM_H
#define MY_E 2.7182818284
#include "model.h"
#include "MyRealNo.h"
#include "Features/featuremanager.h"

typedef struct 
{
    string label;
	double probability;
} SLabelPrblty, *PSLabelPrblty;

typedef struct
{
	string label;
	MyRealNo probability;

}SMLabelprblty, *PSMLabelprblty;

const int MBRMDIM=17;
class MBRM:public Model{
public:
    MBRM();
    MBRM(const string& name);
    ~MBRM();
public:
    int		getRowNumber(){return m_rowNumber;}
    void	setRowNumber(const int rowNumber){m_rowNumber=rowNumber;}
    int		getColNumber(){return m_colNumber;}
    void	setColNumber(const int colNumber){m_colNumber=colNumber;}
    double	getCovFactor(){return m_covFactor;}
    void	setCovFactor(const double covFactor){m_covFactor=covFactor;}
    double	getProFactor(){return m_proFactor;}
    void	setProFactor(const double proFactor){m_proFactor=proFactor;}
public:
    bool	train(const string& label);
    bool	classify(IplImage*	pImage,vector<string>& labels);
private:
    double	possibilityOfLabel(CvMat* pFeatureMatTest, const string& label/*, CArrayString& allLabels*/);
	double	PGJ(CvMat* pTestFeatureMat, CvMat* featuresOfJ/*, double beta*/);
	MyRealNo M_PossibilityOfLabel(CvMat* pFeatureMatTest, const string& label/*, double beta*/);
	double	M_PGJ(CvMat* pFeatureMatTest, CvMat* pFeaturesMatJ/*, double beta*/);


private:
    int		m_rowNumber;//4
    int		m_colNumber;//6
    double	m_covFactor;//10000
    double	m_proFactor;//0

};
#endif
