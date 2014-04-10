#ifndef MODELTYPE_H
#define MODELTYPE_H
#include <string>
#include <vector>

using namespace std;

enum	EModelType{
	MT_UNKNOWN=-1,
	MT_GMM,
	MT_QDA,
	MT_SVM,
    MT_MBRM //Multiple bernoulli relevance models
};
#define MT_NUM	4

class ModelType{
public:
    ModelType();
    ~ModelType();
public:
    static	bool	getAllModelType(vector<string> ModelType);
    static	bool	getAllModelType(EModelType*   ModelType);
public:
    static	string	getModelType(const EModelType& eModelType);
    static	EModelType	getModelType(const string& sModelType);
public:
    static bool isValid(const string& sModelType);
    static bool	isValid(const EModelType& eModelType);
private:
    static EModelType	m_enuModelType[MT_NUM];
    static vector<string>		m_vecModelType;
};
#endif
