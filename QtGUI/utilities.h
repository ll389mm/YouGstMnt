#ifndef UTILITIES_H
#define UTILITIES_H

#include <QTimer>
#include <QWidget>

class Blinker : QObject {
    Q_OBJECT

public:
    Blinker();
    void setWidget(QWidget *widget);
    void exec();

private slots:
    void blink();

private:
    QWidget *widget;
    QString bgColors[2];
    QTimer timer;
    int next;
    int count;
};

#endif // UTILITIES_H
