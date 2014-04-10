/**
 * @file /Core/abstractlabelmanager.h
 * @author Chen Yucong, lionelclark@163.com
 */

#ifndef ABSTRACTLABELMANAGER_H
#define ABSTRACTLABELMANAGER_H

#include "label.h"
#include <list>

/**
 * @brief An abstract label manager class to manage labels.
 *
 * This abstract class is the base class of label manager classes. The pure
 * virtual member functions of this class should be implemented by a concrete
 * label manager class which derives this class.
 *
 * @version 1.0.0
 */
class LabelManager
{
protected:


public:
    LabelManager();
    ~LabelManager();

    static LabelManager* getInstance();

public:
    Label *getLabelByName(const std::string &name);
    bool addLabel(const Label &label);
    bool deleteLabelByName(const std::string &name);
    bool ifLabelExistsByName(const std::string &name);
    int labelCount();

    bool loadLabelsFromDisk(const std::string& configFile="labels.txt");

    /**
     * @brief saveLabelsToDisk
     * @param filename By default, it saves to a name named "labels.txt"
     * TODO: Make the config file structured and, in great later time, DB
     * @return T/F
     */
    bool saveLabelsToDisk(const std::string& filename="labels.txt");

    /**
     * @brief Copy all labels in this manager into a specified label array.
     * @param buf the label array to recieve all returned labels
     * @param n the length of label array, make sure it is large enough to
     *            recieve all the copied labels.
     * @return T/F.
     */
    bool copyAllLabels(std::vector<Label> buf, const int n);

    //Disable copy construction.
    LabelManager(const LabelManager&);
    LabelManager& operator= (const LabelManager&);

private:
    std::list<Label> labels;

    static LabelManager instance;
};

#endif // ABSTRACTLABELMANAGER_H
