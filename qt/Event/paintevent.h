#ifndef PAINTEVENT_H
#define PAINTEVENT_H

#include <QWidget>

class PaintEvent : public QWidget
{
    Q_OBJECT
public:
    explicit PaintEvent(QWidget *parent = nullptr);

signals:

};

#endif // PAINTEVENT_H
