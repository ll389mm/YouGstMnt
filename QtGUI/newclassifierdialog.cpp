#include "newclassifierdialog.h"
#include "ui_newclassifierdialog.h"

NewClassifierDialog::NewClassifierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClassifierDialog) {
    ui->setupUi(this);
    setFixedSize(width(), height());
}

NewClassifierDialog::~NewClassifierDialog() {
    delete ui;
}
