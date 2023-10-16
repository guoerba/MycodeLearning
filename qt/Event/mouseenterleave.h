#ifndef MOUSEENTERLEAVE_H
#define MOUSEENTERLEAVE_H

#include <QWidget>
#include <QLabel>
#include <QEvent>

class MouseEnterLeave : public QWidget
{
    Q_OBJECT
public:
    explicit MouseEnterLeave(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
signals:
private:
    QLabel *downLabel;
    int count = 0;
};

#endif // MOUSEENTERLEAVE_H
