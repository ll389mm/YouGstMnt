#include "Modelmanager.h"

//Initialize and management
ModelManager*	ModelManager::instance=NULL;
ModelManager::ModelManager()
{}
ModelManager::~ModelManager()
{}


//...........................................................
//Preservation management
bool ModelManager::ifModelExistsByName(const std::string &name) {
    std::list<Model>::iterator it(Models.begin());
    while (it != Models.end()) {
        if (name == it->getName()) return true; ++it;
    } return false;
}

bool	ModelManager::addModel(const Model& Model)
{
    if (ifModelExistsByName(Model->getName())) return false;
    Models.insert(Models.end(), *Model);
    return true;
}

bool	ModelManager::delModel(const string& name)
{
    std::list<Model>::iterator it(Models.begin());
    while (it != Models.end()) {
        if (name == it->getName()) {
            Models.erase(it); return true;
        } ++it;
    } return false;
}

unsigned int	ModelManager::getModelCount()
{
    return Models.size();
}

EModelType	ModelManager::getModelType(const string& ModelName)
{
    //to be done as follows:
    //Follow Models and compare names.
}

bool ModelManager::copyAllModels(std::vector<AbstractModel> buf, const int len) {
    if (len < 1) return 0;
    std::list<AbstractModel>::const_iterator it(Models.begin());
    int n = 0;
    while (it != Models.end() && n < len) {
        buf[n] = *it; ++it; ++n;
    }
    return n;
}
