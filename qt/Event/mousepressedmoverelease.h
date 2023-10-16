#ifndef MOUSEPRESSEDMOVERELEASE_H
#define MOUSEPRESSEDMOVERELEASE_H

#include <QWidget>
#include <QLabel>

class MousePressedMoveRelease : public QWidget
{
    Q_OBJECT
public:
    explicit MousePressedMoveRelease(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
signals:
private:
    QLabel *mlabel;
    QWidget *mwin;

    QPoint labelPoint;
    QPoint mousePoint;
};

#endif // MOUSEPRESSEDMOVERELEASE_H
