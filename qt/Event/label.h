#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QWidget>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    int count = 0;
};

#endif // LABEL_H
