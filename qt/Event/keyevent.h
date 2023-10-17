#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
class KeyEvent : public QWidget
{
    Q_OBJECT
public:
    explicit KeyEvent(QWidget *parent = nullptr);

signals:

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QLabel *label;
};

#endif // KEYEVENT_H
