#ifndef DRAGEVENT_H
#define DRAGEVENT_H

#include <QWidget>
#include "texteditx.h"

class DragEvent : public QWidget
{
    Q_OBJECT
public:
    explicit DragEvent(QWidget *parent = nullptr);

signals:
private:
    TextEditX *textEdit;
};

#endif // DRAGEVENT_H
