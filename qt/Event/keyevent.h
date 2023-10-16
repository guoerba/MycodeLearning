#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>

class KeyEvent : public QWidget
{
    Q_OBJECT
public:
    explicit KeyEvent(QWidget *parent = nullptr);

signals:

};

#endif // KEYEVENT_H
