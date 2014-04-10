#include "classifiermanager.h"
#include "commondefinitions.h"
#include <iostream>

ClassifierManager ClassifierManager::instance;

ClassifierManager* ClassifierManager::getInstance()
{
    return &instance;
}

Classifier *ClassifierManager::getClassifierByName(const std::string &name) {
    std::list<Classifier>::iterator it(classifiers.begin());
    while (it != classifiers.end()) {
        if (name == it->getName()) return &*it; ++it;
    } return NULLPOINTER(Classifier);
}

bool ClassifierManager::addClassifier(Classifier* classifier) {
    if (ifClassifierExistsByName(classifier->getName())) return false;
    classifiers.insert(classifiers.end(), *classifier); return true;
}

bool ClassifierManager::deleteClassifierByName(const std::string &name) {
    std::list<Classifier>::iterator it(classifiers.begin());
    while (it != classifiers.end()) {
        if (name == it->getName()) {
            classifiers.erase(it); return true;
        } ++it;
    } return false;
}

bool ClassifierManager::ifClassifierExistsByName(const std::string &name) {
    std::list<Classifier>::iterator it(classifiers.begin());
    while (it != classifiers.end()) {
        if (name == it->getName()) return true; ++it;
    } return false;
}

ClassifierManager::ClassifierManager()
{
}

ClassifierManager::~ClassifierManager() {
    std::cout << "ClassifierManager destruction happens" << std::endl;
}
