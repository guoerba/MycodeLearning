#include "timerevent.h"
#include <QLabel>
#include <QVBoxLayout>

TimerEvent::TimerEvent(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel("定时器事件");
    label->setFrameStyle(QFrame::Box);
    label->setFixedHeight(50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: blue; color: white; font-size: 25px");

    layout->addWidget(label);
}
