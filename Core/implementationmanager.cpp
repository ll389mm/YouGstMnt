#include "implementationmanager.h"
#include "commondefinitions.h"
#include "labelmanager.h"
#include "classifiermanager.h"
#include "Models/modelmanager.h"
#include "Features/featuremanager.h"
#include "networkmanager.h"

#ifdef WIN32
#include "Windows.h"
#else
#include <dlfcn.h>
#endif

#include <iostream>
#include <stdio.h>

ImplementationManager ImplementationManager::instance;

ImplementationManager *ImplementationManager::getInstance()
{
    return &instance;
}

ImplementationManager::ImplementationManager()
{
    //Initialize all managers.

    LabelManager* lm=LabelManager::getInstance();
    ClassifierManager* cm=ClassifierManager::getInstance();
    FeatureManager* fm=FeatureManager::getInstance();
    ModelManager* mm=ModelManager::getInstance();
    NetworkManager* nm=NetworkManager::getInstance();
}

//Configuation file reading and saving.

ImplementationManager::readConfiguation(const string configFileName)
{

}
