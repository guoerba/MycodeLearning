#ifndef TIMEREVENT_H
#define TIMEREVENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimerEvent>

class TimerEvent : public QWidget
{
    Q_OBJECT
public:
    explicit TimerEvent(QWidget *parent = nullptr);

signals:
protected:
    void timerEvent(QTimerEvent *event);

public slots:
    void onbtnStartClicked();
    void onbtnStopClicked();
    void onbtnResetClicked();

private:
    QLabel *labelUp;
    QLabel *labelDown;

    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnReset;

    int timerID1;
    int timerID2;
};

#endif // TIMEREVENT_H
