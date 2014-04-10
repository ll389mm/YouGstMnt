#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <list>
#include "abstractmodel.h"
#include "abstractfeature.h"
#include "label.h"

class Classifier {
public:
    Classifier(std::string n);
    Classifier(std::string n, AbstractModel *m, AbstractFeature *f);

    std::string getName();

    AbstractModel *getModel();
    void setModel(AbstractModel *m);

    AbstractFeature *getFeature();
    void setFeature(AbstractFeature *f);

    bool train(Label *la);

    int labelCounts();

    int getLabels(Label *ls[], int len);

private:
    std::string name;
    AbstractModel *model;
    AbstractFeature *feature;
    std::list<Label*> labels;
};

#endif // CLASSIFIER_H
