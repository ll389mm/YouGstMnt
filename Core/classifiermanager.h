#ifndef ABSTRACTCLASSIFIERMANAGER_H
#define ABSTRACTCLASSIFIERMANAGER_H

#include <string>
#include "classifier.h"

class ClassifierManager {
public:
    ClassifierManager();

public:
    ~ClassifierManager();

    static ClassifierManager* getInstance();

    int counts();

    Classifier *getClassifierByName(const std::string &name);

    bool ifClassifierExistsByName(const std::string &name);

    bool addClassifier(Classifier *cl);

    bool deleteClassifierByName(const std::string &name);

    bool writeClassifiers(const string configFileName = "config.ini");
    bool readClassifiers(const string configFileName = "config.ini");

private:
    std::list<Classifier> classifiers;

    static ClassifierManager instance;
};

#endif // ABSTRACTCLASSIFIERMANAGER_H
