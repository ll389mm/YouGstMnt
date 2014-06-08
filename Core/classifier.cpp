#include "classifier.h"

bool Classifier::train(Label *la) {
    bool re = model->train(feature, la);
    labels.push_back(la); return re;
}

int Classifier::getLabels(Label *ls[], int len) {
    std::list<Label*>::iterator it(labels.begin()); int n = 0;
    while (labels.end() != it && n < len) {
        ls[n] = *it; ++n; ++it;
    } return n;
}
