#ifndef NEWLABELDIALOG_H
#define NEWLABELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "utilities.h"

namespace Ui {
class NewLabelDialog;
}

class NewLabelDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewLabelDialog(QWidget *parent = 0);
    ~NewLabelDialog();
    
private slots:
    void accept();

    void on_pbChoose_clicked();

private:
    Ui::NewLabelDialog *ui;
    QListWidget *lwLabels;
    Blinker *blinker;
};

#endif // NEWLABELDIALOG_H
