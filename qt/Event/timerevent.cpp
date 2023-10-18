#include "timerevent.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

TimerEvent::TimerEvent(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    labelUp = new QLabel();
    labelUp->setFrameStyle(QFrame::Box);
    labelUp->setFixedSize(100, 100);
    labelUp->setAlignment(Qt::AlignCenter);
    labelUp->setStyleSheet("background-color: blue; color: white; font-size: 25px");

    labelDown = new QLabel();
    labelDown->setFrameStyle(QFrame::Box);
    labelDown->setFixedSize(100, 100);
    labelDown->setAlignment(Qt::AlignCenter);
    labelDown->setStyleSheet("background-color: red; color: white; font-size: 25px");

    layout->addWidget(labelUp);
    layout->addWidget(labelDown);

    btnStart = new QPushButton("开始");
    btnStop = new QPushButton("停止");
    btnReset = new QPushButton("复位");
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(btnStart);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnReset);

    layout->addLayout(hLayout);

    this->setStyleSheet("QPushButton{color:white;background:black;font-size:25px}");

    connect(btnStart, &QPushButton::clicked, this, &TimerEvent::onbtnStartClicked);
    connect(btnStop, &QPushButton::clicked, this, &TimerEvent::onbtnStopClicked);
    connect(btnReset, &QPushButton::clicked, this, &TimerEvent::onbtnResetClicked);
}

void TimerEvent::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerID1) {
        labelUp->move(labelUp->x() + 5, labelUp->y());
        labelUp->setText(QString("(%1,%2)").arg(labelUp->x()).arg(labelUp->y()));
        if (labelUp->x() > this->width()) {
            labelUp->move(-labelUp->width(), labelUp->y());
        }
    } else if (event->timerId() == timerID2) {
        labelDown->move(labelDown->x() + 5, labelDown->y());
        labelDown->setText(QString("(%1,%2)").arg(labelDown->x()).arg(labelDown->y()));
        if (labelDown->x() > this->width()) {
            labelDown->move(-labelDown->width(), labelDown->y());
        }
    }
}

void TimerEvent::onbtnStartClicked()
{
    timerID1 = startTimer(10);
    timerID2 = startTimer(50);
}

void TimerEvent::onbtnStopClicked()
{
    killTimer(timerID1);
    killTimer(timerID2);
}

void TimerEvent::onbtnResetClicked()
{
    labelUp->move(0, labelUp->y());
    labelDown->move(0, labelDown->y());
    labelUp->setText(QString("(%1,%2)").arg(labelUp->x()).arg(labelUp->y()));
    labelDown->setText(QString("(%1,%2)").arg(labelDown->x()).arg(labelDown->y()));
}
