#include "abstractmodel.h"

AbstractModel::AbstractModel() {}

AbstractModel::~AbstractModel() {}

const std::string AbstractModel::getName()
{
    return name;
}

bool AbstractModel::train(AbstractFeature *f, Label *l)
{
    //to be added
}
