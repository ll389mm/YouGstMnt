#ifndef NEWCLASSIFIERDIALOG_H
#define NEWCLASSIFIERDIALOG_H

#include <QDialog>

namespace Ui {
class NewClassifierDialog;
}

class NewClassifierDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewClassifierDialog(QWidget *parent = 0);
    ~NewClassifierDialog();
    
private:
    Ui::NewClassifierDialog *ui;
};

#endif // NEWCLASSIFIERDIALOG_H
