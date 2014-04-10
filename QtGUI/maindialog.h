#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "utilities.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    
private slots:
    void reject();

    void on_pbNewLabel_clicked();

    void on_pbNewClassifier_clicked();

    void on_pbTrain_clicked();

    void on_pbEditLabel_clicked();

    void on_pbEditClassifier_clicked();

    void on_pbRecognizeImage_clicked();

    void on_pbDeleteLabel_clicked();

    void on_pbDeleteClassifier_clicked();

    void on_cbPort_stateChanged(int state);

    void on_lePort_textChanged(const QString &text);

    void on_pbStart_clicked();

    void on_pbSuspend_clicked();

    void on_pbStop_clicked();

private:
    void initCommandsGroupBox();
    void initOptionsGroupBox();
    void initLabelsGroupBox();
    void initClassifiersGroupBox();

private:
    Ui::MainDialog *ui;
    Blinker *blinker;
};

#endif // MAINDIALOG_H
