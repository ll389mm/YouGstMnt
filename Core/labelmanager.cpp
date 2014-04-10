#include "labelmanager.h"
#include "commondefinitions.h"
#include <iostream>
#include <fstream>

LabelManager LabelManager::instance;

LabelManager* LabelManager::getInstance()
{
    return &instance;
}

/*Construction Function:
 *The construction function will initiate all labels into memory from configuation file.
 *The configuation file is in the following format:
 *<Label Name>
 *<Label Path>
 *and so on.
*/

LabelManager::LabelManager()
{
    std::cout<<"LabelManager construction happens."<<std::endl;
    loadLabelsFromDisk();
}


Label *LabelManager::getLabelByName(const std::string &name) {
    std::list<Label>::iterator it(labels.begin());
    while (it != labels.end()) {
        if (name == it->getName())
            return &*it;
        ++it;
    }
    return NULLPOINTER(Label);
}

bool LabelManager::addLabel(const Label &label) {
    if (ifLabelExistsByName(label.getName()))
        return false;
    labels.insert(labels.end(), label);
    return true;
}

bool LabelManager::deleteLabelByName(const std::string &name) {
    std::list<Label>::iterator it(labels.begin());
    while (it != labels.end()) {
        if (name == it->getName()) {
            labels.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

bool LabelManager::ifLabelExistsByName(const std::string &name) {
    std::list<Label>::iterator it(labels.begin());
    while (it != labels.end()) {
        if (name == it->getName())
            return true;
        ++it;
    }
    return false;
}

int LabelManager::labelCount() {
    return labels.size();
}

bool LabelManager::copyAllLabels(std::vector<Label> buf, const int len) {
    if (len < 1) return 0;
    std::list<Label>::const_iterator it(labels.begin());
    int n = 0;
    while (it != labels.end() && n < len) {
        buf[n] = *it;
        ++it;
        ++n;
    }
    return n;
}

LabelManager::~LabelManager() {
    saveLabelsToDisk();
    std::cout << "LabelManager destruction happens, all configs saved" << std::endl;
}

bool LabelManager::saveLabelsToDisk(const std::string &name)
{
    std::ofstream out;
    out.open(name.c_str(),std::ofstream::out|std::ofstream::trunc);
    //Truncate the file upun saving.
    if (out)
    {
        for (auto it:labels)
        {
            out<<it.getName()<<std::endl;
            out<<it.getImageDirectory()<<std::endl;
        }
        out.close();
        std::cout<<"Labels saved to disk successfully"<<std::endl;
        return true;
    }
    return false;
}


bool LabelManager::loadLabelsFromDisk(const std::string &configFile)
{
    std::ifstream in(configFile.c_str());
    std::string inString;
    std::string labelName,labelPath;
    int i=0;
    while(std::getline(in,inString))
    {
        i++;
        if (i%2!=0)
            labelName=inString;
        else
        {
            labelPath=inString;
            Label newLabel=Label(labelName,labelPath);
            addLabel(newLabel);
        }
    }
    std::cout<<"Labels loaded from disk successfully"<<std::endl;
    return true;
}
