#include <QApplication>
#include "maindialog.h"
#include "commondefinitions.h"
#include "implementationmanager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); MainDialog md; md.show();
    int exitCode = app.exec();
    ImplementationManager *im = ImplementationManager::getInstance();
    return exitCode;
}
