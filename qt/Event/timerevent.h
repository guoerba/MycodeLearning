#ifndef TIMEREVENT_H
#define TIMEREVENT_H

#include <QWidget>

class TimerEvent : public QWidget
{
    Q_OBJECT
public:
    explicit TimerEvent(QWidget *parent = nullptr);

signals:

};

#endif // TIMEREVENT_H
