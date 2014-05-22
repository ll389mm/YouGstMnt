#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <list>
#include "abstractmodel.h"
#include "label.h"

class Classifier {
public:
    Classifier(std::string n);
    Classifier(std::string n, AbstractModel *m, Feature *f);

    std::string getName();

    AbstractModel *getModel();
    void setModel(AbstractModel *m);

    Feature *getFeature();
    void setFeature(Feature *f);

    bool train(Label *la);

    int labelCounts();

    int getLabels(Label *ls[], int len);

private:
    std::string name;
    AbstractModel *model;
    Feature *feature;
    std::list<Label*> labels;
};

#endif // CLASSIFIER_H
