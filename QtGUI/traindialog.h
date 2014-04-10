#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

#include <QDialog>

namespace Ui {
class TrainDialog;
}

class TrainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TrainDialog(QWidget *parent = 0);
    ~TrainDialog();
    
private:
    Ui::TrainDialog *ui;
};

#endif // TRAINDIALOG_H
