#ifndef EDITLABELDIALOG_H
#define EDITLABELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "utilities.h"

namespace Ui {
class EditLabelDialog;
}


class EditLabelDialog : public QDialog
{
    //QObject defined by Qt.
    Q_OBJECT
    
public:
    explicit EditLabelDialog(QWidget *parent = 0);
    ~EditLabelDialog();
    
private slots:
    void accept();
    void on_pbChoose_clicked();

private:
    Ui::EditLabelDialog *ui;
    QListWidget *lwLabels;
    Blinker *blinker;
};

#endif // EDITLABELDIALOG_H
