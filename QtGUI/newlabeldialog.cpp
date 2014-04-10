#include "newlabeldialog.h"
#include "ui_newlabeldialog.h"
#include "maindialog.h"
#include <stdlib.h>
#include <QFileDialog>
#include "label.h"
#include "labelmanager.h"
#include "utilities.h"
#include "commondefinitions.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include "implementationmanager.h"

NewLabelDialog::NewLabelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewLabelDialog),
    lwLabels(parent->findChild<QListWidget *>("lwLabels")),
    blinker(new Blinker()) {
    ui->setupUi(this);
    setFixedSize(width(), height());
    ui->leName->setFocus();
}

NewLabelDialog::~NewLabelDialog() {
    delete ui;
    delete blinker;
}

void NewLabelDialog::accept() {
    LabelManager *lm = LabelManager::getInstance();

    QString name = ui->leName->text().trimmed();
    if (name.isEmpty() || lm->ifLabelExistsByName(name.toUtf8().data())) {
        blinker->setWidget(ui->leName); blinker->exec();
        ui->leName->setFocus();
        return;
    }

    QString imageDirectory = ui->leImageDirectory->text().trimmed();
    DIR *dir = opendir(imageDirectory.toUtf8().data());
    if (!dir) {
        blinker->setWidget(ui->leImageDirectory);
        blinker->exec();
        closedir(dir);
        ui->leImageDirectory->setFocus();
        return;
    }
    closedir(dir);

    Label label(name.toUtf8().data(), imageDirectory.toUtf8().data());
    bool add = lm->addLabel(label);

    QListWidgetItem *item = new QListWidgetItem(name);
    item->setTextAlignment(Qt::AlignHCenter);
    if (add) lwLabels->addItem(item);
    QDialog::accept();
}

void NewLabelDialog::on_pbChoose_clicked() {
    static QString dirName(getenv("HOME"));
    QString dN = QFileDialog::getExistingDirectory(this, "Choose Image Directory", dirName);
    if (dN.isEmpty())
        return;
    dirName=dN;
    ui->leImageDirectory->setText(dirName + (dN == "/" ? "" : "/"));
}
