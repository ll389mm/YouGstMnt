#include "classifier.h"

Classifier::Classifier(std::string n) : name(n) {}

Classifier::Classifier(std::string n, AbstractModel *m, AbstractFeature *f) :
    name(n), model(m), feature(f) {}

std::string Classifier::getName() {return name;}

AbstractModel *Classifier::getModel() {return model;}

void Classifier::setModel(AbstractModel *m) {model = m;}

AbstractFeature *Classifier::getFeature() {return feature;}

void Classifier::setFeature(AbstractFeature *f) {feature = f;}

bool Classifier::train(Label *la) {
    bool re = model->train(feature, la);
    labels.push_back(la); return re;
}

int Classifier::labelCounts() {return labels.size();}

int Classifier::getLabels(Label *ls[], int len) {
    std::list<Label*>::iterator it(labels.begin()); int n = 0;
    while (labels.end() != it && n < len) {
        ls[n] = *it; ++n; ++it;
    } return n;
}
