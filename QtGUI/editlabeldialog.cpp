#include <QFileDialog>
#include <string>

#include "editlabeldialog.h"
#include "ui_editlabeldialog.h"
#include "dirent.h"
#include "stdlib.h"

#include "labelmanager.h"
#include "implementationmanager.h"

EditLabelDialog::EditLabelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLabelDialog),
    lwLabels(parent->findChild<QListWidget *>("lwLabels")),
    blinker(new Blinker())
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    ui->leImageDirectory->setFocus();

    QString name(lwLabels->currentItem()->text());
    ui->leName->setText(name);
    ui->leName->setReadOnly(true);
    ui->leName->setStyleSheet("background-color: rgb(240,240,240);");

    LabelManager *lm = LabelManager::getInstance();
    Label* tempLabel=lm->getLabelByName(name.toUtf8().data());
    std::string dirString=tempLabel->getImageDirectory();
    ui->leImageDirectory->setText(QString::fromUtf8(dirString.c_str()));
    delete tempLabel;
}

EditLabelDialog::~EditLabelDialog() {
    delete ui; delete blinker;
}

void EditLabelDialog::accept() {
    QString imageDir(ui->leImageDirectory->text().trimmed());
    DIR *dir = opendir(imageDir.toUtf8().data());
    if (!dir) {
        blinker->setWidget(ui->leImageDirectory);
        blinker->exec();
        closedir(dir);
        ui->leImageDirectory->setFocus();
        return;
    }
    closedir(dir);

    LabelManager *lm =LabelManager::getInstance();
    std::string labelName=ui->leName->text().toUtf8().data();
    Label* tempLabel=lm->getLabelByName(labelName);
    tempLabel->setImageDirectory(imageDir.toUtf8().data());
    QDialog::accept();
}

void EditLabelDialog::on_pbChoose_clicked() {
    static QString dirName(getenv("HOME"));
    QString dN = QFileDialog::getExistingDirectory(this, "Choose Image Directory", dirName);
    if (dN.isEmpty()) return;
    ui->leImageDirectory->setText((dirName = dN) + (dN == "/" ? "" : "/"));
}
