#include "model.h"
#include "feature/featuremanager.h"


Model::Model()
{
    m_modelType=MT_MBRM;
}
Model::Model(const string& name)
{
	m_name=name;
    m_modelType=MT_MBRM;
}
Model::Model(const Model& model)
{
    m_name= model.getName();
    string feature;
    m_feature = model.getFeature();
    //setFeature(feature);
    m_modelType=model.getModelType();
}
Model::~Model()
{
}
//.............................................................
string	Model::getName()const
{
	if(m_name.empty()){


        return "";
	}else{

        return m_name;
	}
}
void	Model::setName(const string& name)
{
	m_name=name;
}
Feature	Model::getFeature()const
{
    return m_feature;

}
void	Model::setFeature(const Feature& feature)
{
    m_feature = feature;
}
EModelType	Model::getModelType()const
{

        return m_modelType;

}
void	Model::setModelType(const EModelType& modelType)
{

		m_modelType=modelType;

}
//.............................................................
bool	Model::hasName()//check if the model def is specified.
{
	return !m_name.empty();
}
bool	Model::isExists()const{
    return false;//CDataManager::IsModelDefExists(m_name);
}
bool	Model::isValid()const// test if all member have valid value
{
    string	feature;
    m_feature.getName(feature);
    if(m_name.empty()||feature.empty()||!ModelType::isValid(m_modelType))
		return false;
	else 
		return true;
}
//.............................................................
bool	Model::load(const string& label)
{
   /* string	defFile=CEnvUtil::GetModelDataFile(m_name,label);

	_tifstream	ifs(defFile.c_str());
	if(!ifs){
        CLogManager::Get()->Append(string(_T("Model::Load@ Fail to open modelDef file.")));
		return false;
	}
    string	modelType,featureDef;
	try{
		getline(ifs,featureDef);
		SetFeatureDef(featureDef);
		getline(ifs,modelType);
		m_modelType=static_cast<EModelType>(::_ttoi(modelType.c_str()));
	}catch(...){
		ifs.close();
		return false;
	}
	ifs.close();
    */
	return true;
}
bool	Model::load()
{
   /* string	defFile=CEnvUtil::GetModelDefFile(m_name);

	_tifstream	ifs(defFile.c_str());
	if(!ifs){
        CLogManager::Get()->Append(string(_T("Model::Load@ Fail to open modelDef file.")));
		return false;
	}
    string	modelType,featureDef;
	try{
		getline(ifs,featureDef);
		SetFeatureDef(featureDef);
		getline(ifs,modelType);
		m_modelType=static_cast<EModelType>(::_ttoi(modelType.c_str()));
	}catch(...){
		ifs.close();
		return false;
	}
	ifs.close();
    */
	return true;
}
bool	Model::save(const string& label)
{
    /*string	defFile=CEnvUtil::GetModelDataFile(m_name,label);

	_tofstream	ofs(defFile.c_str());
	if(!ofs){
        CLogManager::Get()->Append(string(_T("Model::Save@ Fail to open modelDef file.")));
		return false;
	}
    string featureDef;
	m_featureDef.GetName(featureDef);
	try{
		ofs<<featureDef<<endl;
		ofs<<m_modelType<<endl;
	}catch(...){
		ofs.close();
		return false;
	}
	ofs.close();
    */
	return true;
}
bool	Model::save()const
{
   /* string	defFile=CEnvUtil::GetModelDefFile(m_name);

	_tofstream	ofs(defFile.c_str());
	if(!ofs){
        CLogManager::Get()->Append(string(_T("Model::Save@ Fail to open modelDef file.")));
		return false;
	}
    string featureDef;
	m_featureDef.GetName(featureDef);
	try{
		ofs<<featureDef<<endl;
		ofs<<m_modelType<<endl;
	}catch(...){
		ofs.close();
		return false;
	}
	ofs.close();
    */
	return true;
}
