#include "utilities.h"
#include "commondefinitions.h"

Blinker::Blinker() {
    bgColors[0] = "white"; bgColors[1] = "magenta"; next = 1;
    connect(&timer, SIGNAL(timeout()), this, SLOT(blink()));
    timer.setInterval(200); widget == NULLPOINTER(QWidget);
}

void Blinker::setWidget(QWidget *widget) {
    this->widget = widget;
}

void Blinker::exec() {
    if (NULLPOINTER(QWidget) == widget) return;
    count = 6;
    timer.start();
}

void Blinker::blink() {
    widget->setStyleSheet("background-color: " + bgColors[next]);
    next = (next + 1) % 2; --count;
    if (count < 0) {
        timer.stop();
        widget->setStyleSheet("background-color: " + bgColors[0]);
    }
}
