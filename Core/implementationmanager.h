#ifndef IMPLEMENTATIONMANAGER_H
#define IMPLEMENTATIONMANAGER_H

#include <string>
#include <map>
#include <vector>

class ImplementationManager
{

private:
    ImplementationManager();

public:
    static ImplementationManager *getInstance();

    bool writeConfiguation(const std::string configFileName);

    bool readConfiguation(const std::string configFileName);

private:
    static ImplementationManager instance;

};

#endif // IMPLEMENTATIONMANAGER_H
