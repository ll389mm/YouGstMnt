/**
 * @file /Core/label.h
 * @author Chen Yucong, lionelclark@163.com
 */

#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <vector>
#include "commondefinitions.h"

/**
 * @brief This class represents a label for annotation.
 *
 * This class represents a label, which contains two fields:
 *     (1) label name, which is the internal name (or short name) of the label;
 *     (2) image directory, in which the sample images holding the label
 *         reside;
 * Make sure that this class shouldn't be subclassed, which means that Label is
 * designated as a 'final' class.
 *
 * @version 1.0.0
 */
class Label {
public:
    Label(const std::string &name = EMPTYSTRING,
          const std::string &imageDirectory = EMPTYSTRING);
    Label(const Label &label);

public:
    std::string getName() const;
    std::string getImageDirectory() const;
    void setImageDirectory(const std::string &imgDir);

private:
    // Here goes the two fields.
    std::string name;
    std::string imageDirectory;
};

#endif // LABEL_H
