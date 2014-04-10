#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "model.h"
#include "MBRM.h"
#include "mysvm.h"
#include <vector>
#include <string>
#include <list>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
class ModelManager
{
private:
    static	ModelManager*	instance;
public:
    ModelManager();
    ~ModelManager();

public:
    static ModelManager*	getInstance(){
        if(instance==NULL){
            instance=new ModelManager();
        }
        return instance;
    }

    static void	free(){
        if(instance!=NULL){
            delete instance;
        }
        instance=NULL;
    }
//:::::::::::::::::::::::::::持久化管理::::::::::::::::::::::::::::::::::::::::::::::::::
public:
    bool	addModel(const Model& Model);
    bool	delModel(const string& name);
    unsigned int	getModelCount();
    EModelType	getModelType(const string& ModelName);
    bool	ifModelExistsByName(const string& name)const;
    bool	updateModel(const string& name,const Model& Model);
    bool    copyAllModels(std::vector<AbstractModel> buf, const int len);
    //Copy all existing Models to a new vector-buffer defined by buf.
private:
    std::list<Model> Models;
#endif // MODELMANAGER_H
