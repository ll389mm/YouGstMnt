#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <string>
#include <vector>
#include "label.h"
#include "Features/feature.h"

class AbstractModel {
public:
    AbstractModel();

public:
    ~AbstractModel();

    std::string getType();

    int paramNames(std::vector<std::string> pns, int len);

    void setParam(std::string &pName, std::string &value);

    std::string getParam(std::string &pName);

    int availFeatureTypeCounts();

    int availFeatureTypes(std::vector<std::string> fns, int len);

    bool train(Feature *f, Label *l);

    const std::string getName();

private:
    std::string name;
};

#endif // ABSTRACTMODEL_H
