#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <list>
#include "Models/model.h"
#include "label.h"

class Classifier {
public:
    Classifier(std::string n) : name(n) {}
    Classifier(std::string n, AbstractModel *m, Feature *f) : name(n), model(m), feature(f) {}

    std::string getName() {return name;}

    Model *getModel() {return model;}
    void setModel(Model *m) {model = m;}

    Feature *getFeature() {return feature;}
    void setFeature(Feature *f) {feature = f;}

    bool train(Label *la);

    int labelCounts() { return labels.size(); }

    int getLabels(Label *ls[], int len);

private:
    std::string name;
    Model *model;
    Feature *feature;
    std::list<Label*> labels;
};

#endif // CLASSIFIER_H
