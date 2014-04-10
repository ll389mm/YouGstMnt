#ifndef MODEL_H
#define MODEL_H

#include "Features/feature.h"
#include "modeltype.h"

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

class Model{
public:
    Model();
    Model(const string& name);
    Model(const Model& model);
    virtual ~Model();
public:
    string	getName()const;
    void	setName(const string& name);
   Feature	getFeature()const;
    void	setFeature(const Feature& feature);
    EModelType	getModelType()const;
    void	setModelType(const EModelType& modelType);
public:
    bool	hasName();//
    bool 	isExists()const;//
    virtual bool	isValid()const;//
public:
    virtual bool	load(const string& label);
    virtual bool	load();
    virtual bool	save(const string& label);
    virtual bool	save()const;
public:
    virtual bool	train(const string& label){
		return false;
	}
    virtual bool	classify(Mat& img,vector<string>& labels){
		return false;
	}
protected:
    string          m_name;
	EModelType		m_modelType;
    Feature         m_feature;
};
#endif
