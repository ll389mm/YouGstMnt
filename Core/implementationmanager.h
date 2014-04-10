/**********************************************************************
ImpMgr initializes configuation on application startup and shutdown.
It reinitializes necessary data structures according to configuation file and manages conf files.
Configuation file format:
[labels]
label1.name=xxx
label1.filepath=xxx
...
[classifiers]
classifier1.xxx
...

By Wang, 2014-4-10
***********************************************************************/

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
