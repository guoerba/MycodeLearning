#ifndef RIGHTCLICKEDEVENT_H
#define RIGHTCLICKEDEVENT_H

#include <QWidget>

class RightClickedEvent : public QWidget
{
    Q_OBJECT
public:
    explicit RightClickedEvent(QWidget *parent = nullptr);

signals:

};

#endif // RIGHTCLICKEDEVENT_H
