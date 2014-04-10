#include "traindialog.h"
#include "ui_traindialog.h"

TrainDialog::TrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainDialog) {
    ui->setupUi(this);
    setFixedSize(width(), height());
}

TrainDialog::~TrainDialog() {
    delete ui;
}
