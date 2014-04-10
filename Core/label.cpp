#include "label.h"

Label::Label(const std::string &name, const std::string &imageDirectory)
    : name(name), imageDirectory(imageDirectory) {}

Label::Label(const Label &label)
    : name(label.name), imageDirectory(label.imageDirectory) {}

std::string Label::getName() const {
    return name;
}

std::string Label::getImageDirectory() const {
    return imageDirectory;
}

void Label::setImageDirectory(const std::string &imgDir) {
    imageDirectory = imgDir;
}
