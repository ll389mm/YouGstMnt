#include "maindialog.h"
#include "ui_maindialog.h"
#include "newlabeldialog.h"
#include "editlabeldialog.h"
#include "newclassifierdialog.h"
#include "traindialog.h"
#include <QApplication>
#include <QFileDialog>
#include <stdlib.h>
#include <QMessageBox>
#include <iostream>
#include "commondefinitions.h"
#include "implementationmanager.h"
#include "labelmanager.h"
#include "featuremanager.h"
#include "modelmanager.h"
#include "classifiermanager.h"


MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    blinker(new Blinker()) {
    ui->setupUi(this);
    initCommandsGroupBox();
    initOptionsGroupBox();
    initLabelsGroupBox();
    initClassifiersGroupBox();
    setFixedSize(width(), height());
}

MainDialog::~MainDialog() {
    delete ui;
    delete blinker;
}

//-------------------------Initiate commands-----------------------
void MainDialog::initCommandsGroupBox() {
    ui->pbStart->setEnabled(true);
    ui->pbSuspend->setEnabled(false);
    ui->pbStop->setEnabled(false);
    ui->pbRecognizeImage->setEnabled(false);
}

void MainDialog::initOptionsGroupBox() {
    ui->cbPort->setEnabled(false);
}

void MainDialog::initLabelsGroupBox() {
}

void MainDialog::initClassifiersGroupBox() {
}

void MainDialog::reject() {
    if (!ui->pbStart->isEnabled()) return;
    QMessageBox mb(QMessageBox::NoIcon,
                   "Quit Program",
                   "Do you want to quit this program?",
                   QMessageBox::No | QMessageBox::Yes,
                   this);
    if (QMessageBox::Yes == mb.exec()) QDialog::reject();
}

//-----------------------Button processing--------------------------------
void MainDialog::on_pbStart_clicked() {
    ui->pbStart->setEnabled(false);
    ui->pbSuspend->setEnabled(true);
    ui->pbStop->setEnabled(true);
    ui->pbRecognizeImage->setEnabled(true);

    ui->gbOptions->setEnabled(false);
    ui->gbLabels->setEnabled(false);
    ui->gbClassifiers->setEnabled(false);

    //fork and exec the server.

}

//Possibily useless and might be removed, as we now use a separate server process.
void MainDialog::on_pbSuspend_clicked() {
    if ("suspend" == ui->pbSuspend->text()) {
        ui->pbSuspend->setText("resume");
        ui->pbRecognizeImage->setEnabled(false);
    } else if ("resume" == ui->pbSuspend->text()) {
        ui->pbSuspend->setText("suspend");
        ui->pbRecognizeImage->setEnabled(true);
    }
}

//Send SIGINT to the server.
void MainDialog::on_pbStop_clicked() {
    ui->pbStart->setEnabled(true);
    ui->pbSuspend->setText("suspend");
    ui->pbSuspend->setEnabled(false);
    ui->pbStop->setEnabled(false);
    ui->pbRecognizeImage->setEnabled(false);

    ui->gbOptions->setEnabled(true);
    ui->gbLabels->setEnabled(true);
    ui->gbClassifiers->setEnabled(true);
}

void MainDialog::on_pbRecognizeImage_clicked() {
    static QString fileName(getenv("HOME"));
    QString fN = QFileDialog::getOpenFileName(
                this, "Open Image", fileName,
                "Image Files (*.png *.jpg *.bmp);;All Files (*)");
    if (fN.isEmpty()) return;
    ui->pbRecognizeImage->setText((fileName = fN).split("/").last());
    ui->pbRecognizeImage->setStyleSheet("background-color: rgb(127,127,0)");
}

void MainDialog::on_pbNewLabel_clicked() {
    NewLabelDialog nld(this);
    nld.exec();
}

void MainDialog::on_pbEditLabel_clicked() {
    QListWidgetItem *item = ui->lwLabels->currentItem();
    if (!item) {
        blinker->setWidget(ui->lwLabels);
        blinker->exec();
        return;
    }
    EditLabelDialog eld(this);
    eld.exec();
}

void MainDialog::on_pbDeleteLabel_clicked() {
    QListWidgetItem *item = ui->lwLabels->currentItem();
    if (!item) {
        blinker->setWidget(ui->lwLabels);
        blinker->exec(); return;
    }
    QMessageBox mb(QMessageBox::NoIcon,
                   "Delete Label",
                   "Do you want to delete label: \"" +
                   item->text() + "\" ?",
                   QMessageBox::No | QMessageBox::Yes,
                   this);
    if (QMessageBox::Yes == mb.exec()) {
        LabelManager* lm = LabelManager::getInstance();
        lm->deleteLabelByName(item->text().toUtf8().data());
        delete item;
    }
}

void MainDialog::on_pbNewClassifier_clicked() {
    NewClassifierDialog ncd(this);
    ncd.exec();
}

void MainDialog::on_pbEditClassifier_clicked() {
    NewClassifierDialog ncd(this);
    ncd.setWindowTitle("Edit Classifier");
    ncd.exec();
}

void MainDialog::on_pbDeleteClassifier_clicked() {
    QMessageBox mb(QMessageBox::NoIcon,
                   "Delete Classifier",
                   "Do you want to delete this classifier?",
                   QMessageBox::No | QMessageBox::Yes,
                   this);
    if (QMessageBox::Yes == mb.exec()) {

    }
}

void MainDialog::on_pbTrain_clicked() {
    TrainDialog td(this);
    td.exec();
}

void MainDialog::on_cbPort_stateChanged(int state) {
    if (Qt::Checked == state) {
        ui->lePort->setEnabled(false);
    } else if (Qt::Unchecked == state) {
        ui->lePort->setEnabled(true);
    } else {}
}

//TODO:Set port used by server. This can be passed by using command line options, or configuation files.
void MainDialog::on_lePort_textChanged(const QString &text) {
    bool ok; int port = text.toInt(&ok);
    if ((text.isEmpty() || ok) && port >= 0 && port <= 65535) {
        if (!text.isEmpty()) ui->cbPort->setEnabled(true);
        else ui->cbPort->setEnabled(false);
    } else {
        blinker->setWidget(ui->lePort);
        blinker->exec();
        ui->cbPort->setEnabled(false);
    }
}
